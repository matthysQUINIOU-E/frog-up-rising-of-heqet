#include "pch.h"
#include "Camera.h"
#include "Controller.h"
#include "SceneTag.h"
#include "GameVariables.h"
#include "Frog1.h"
#include "Frog2.h"


using namespace nam;
using namespace DirectX;

void Camera::OnInit()
{
    AddComponent<TransformComponent>({});
    AddComponent<CameraComponent>({});
    AddComponent<CameraTag>({});

    SetBehavior();
    SetController();
}

void Camera::OnUpdate()
{
    Ecs& ecs = App::Get()->GetEcs();
    if (m_frogToFollow == 0)
    {
        ecs.ForEach<Frog1Tag, TransformComponent>([&](uint32_t entity, Frog1Tag& tag, TransformComponent& transform)
        {
            m_targetToFollow = transform.GetWorldPosition();
        });
    }
    else if (m_frogToFollow == 1)
    {
        ecs.ForEach<Frog2Tag, TransformComponent>([&](uint32_t entity, Frog2Tag& tag, TransformComponent& transform)
        {
            m_targetToFollow = transform.GetWorldPosition();
        });
    }
}

void Camera::OnController()
{
    App* app = App::Get();

    if (Controller::Get(ControlType::Pause))
    {
        m_cursorUse = !m_cursorUse;
        app->GetChrono().SetFreezeState(m_cursorUse);
        app->CreateOrGetScene<Scene>((size)SceneTag::Pause).SetActive(m_cursorUse);
        GameVariables::s_isGamePaused = m_cursorUse;

        if (!m_cursorUse)
        {
            Window& window = app->GetWindow();
            XMFLOAT2 size = XMFLOAT2((float)window.m_clientWidth, (float)window.m_clientHeight);
            XMFLOAT2 centerSize = XMFLOAT2(size.x * 0.5f, size.y * 0.5f);
            Input::SetMousePosition(centerSize);
            Input::UpdateMouseDelta();
        }
    }

    if (m_cursorUse)
        Input::ShowMouse();

    if (GameVariables::s_isGamePaused)
        return;
    else if (m_cursorUse)
        m_cursorUse = !m_cursorUse;

    if (Controller::Get(ControlType::SwitchFrog1))
        m_frogToFollow = 0;

    if (Controller::Get(ControlType::SwitchFrog2))
        m_frogToFollow = 1;

    TransformComponent& transform = GetComponent<TransformComponent>();

    if (!m_cursorUse)
    {
        Input::HideMouse();

        Window& window = app->GetWindow(); // TODO :: stock center inside window directly
        XMFLOAT2 size = XMFLOAT2((float)window.m_clientWidth, (float)window.m_clientHeight);
        XMFLOAT2 centerSize = XMFLOAT2(size.x * 0.5f, size.y * 0.5f);
        Input::UpdateMouseDelta();
        XMFLOAT2 delta = Input::GetMouseDelta();
        Input::SetMousePosition(centerSize);

        transform.RotateAroundWorld(m_targetToFollow, transform.GetWorldUp(), (float)delta.x * m_sensitivity);
        transform.RotateAroundWorld(m_targetToFollow, transform.GetWorldRight(), (float)delta.y * m_sensitivity);

    }

    XMFLOAT3 forward = transform.GetWorldForward();
    XMFLOAT3 newPos;
    newPos.x = m_targetToFollow.x - forward.x * m_distanceFromTarget;
    newPos.y = m_targetToFollow.y - forward.y * m_distanceFromTarget;
    newPos.z = m_targetToFollow.z - forward.z * m_distanceFromTarget;

    transform.SetWorldPosition(newPos);

    transform.LookAtWorld(m_targetToFollow);

}

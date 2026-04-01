#include "pch.h"
#include "Frog.h"
#include "Camera.h"
#include "Constant.h"
#include "FrogArrow.h"
#include "ColliderTag.h"

using namespace nam;
using namespace DirectX;

void Frog::OnInit()
{
    MeshRendererComponent mrc;
    mrc.CreateMeshInstance();
    mrc.mp_mesh->BuildBox({ 1.f,1.f, 1.f }, { 0.5f,0.5f,0.5f,1.f });
    AddComponent<MeshRendererComponent>(mrc);

    TransformComponent tc;
    tc.SetWorldPosition({ -1.f,2.f,0.f });
    AddComponent<TransformComponent>(tc);

    AddComponent<PhysicComponent>(PhysicComponent());

    Scene& scene = GetScene();
    m_arrow = &scene.CreateGameObject<FrogArrow>(false);
    TransformComponent& arrowTransform = m_arrow->GetComponent<TransformComponent>();
    arrowTransform.SetParent(&GetComponent<TransformComponent>());  
    m_arrowTimer.Init(m_targetTime);
}

void Frog::OnUpdate()
{
    float dt = App::Get()->GetChrono().GetScaledDeltaTime();
    m_arrowTimer.Update(dt);

    if (m_arrowTimer.IsTargetReached())
    {
        m_arrow->SetActive(false);
        m_arrowTimer.ResetProgress();
    }

    if (m_isSpacePressed && (m_isGrounded || m_isOnWall))
        ChargeJump();

    if (m_isOrientedWall == false)
    {
        RotateUpdate();
        //Rotate();
    }
}

void Frog::OnController()
{
    ControllerJump();

    InclineArrow();

    ControllerMove();
}
   

void Frog::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
    PhysicComponent& physic = GetComponent<PhysicComponent>();
    TransformComponent& transform = GetComponent<TransformComponent>();

    bool onPlateform = (other.m_tag == (size)ColliderTag::Platform) && self.m_normal.y < 0.f;
    bool onFloor = other.m_tag == (size)ColliderTag::Ground;

    if (onPlateform || onFloor)
    {
        XMFLOAT3 up = transform.GetWorldUp();
        XMFLOAT3 normal = other.m_normal;

        XMVECTOR vUp = XMLoadFloat3(&up);
        XMVECTOR vOtherNormal = XMLoadFloat3(&normal);

        XMVECTOR vSub = vUp - vOtherNormal;
        XMFLOAT3 sub;
        XMStoreFloat3(&sub, vSub);

        if( abs(sub.x) <= EPSILON && abs(sub.y) <= EPSILON && abs(sub.z) <= EPSILON)
            physic.m_useGravity = false;
        else
            physic.m_useGravity = true;

        
        m_isGrounded = true;
        m_isOnWall = false;
        m_isOrientedWall = false;
        physic.m_dirGravity = self.m_normal;
        physic.m_velocity = { 0.f,0.f,0.f };
        m_normal = other.m_normal;

        if (m_normal.y == 1)
        {
            transform.SetWorldUp(m_normal);
            Print("FORWARD : ", transform.GetWorldForward().x, " / ", transform.GetWorldForward().y, " / ", transform.GetWorldForward().z);
        }
        else
        {
            XMVECTOR vNormal = XMLoadFloat3(&m_normal);

            XMVECTOR vGlobalUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);
            XMVECTOR vRight = XMVector3Normalize(XMVector3Cross(vGlobalUp, vNormal));

            XMVECTOR vForward = XMVector3Normalize(XMVector3Cross(vNormal, vRight));

            XMFLOAT3 newForward;
            XMStoreFloat3(&newForward, vForward);

            transform.LookToWorld(newForward, m_normal);

            Print("FORWARD : ", transform.GetWorldForward().x, " / ", transform.GetWorldForward().y, " / ", transform.GetWorldForward().z);
        }
    }
}

void Frog::ChargeJump()
{
    float dt = App::Get()->GetChrono().GetScaledDeltaTime();
    m_jumpImpulse += m_maxImpulse * dt * m_chargeJumpRate;
    m_jumpImpulse = std::clamp(m_jumpImpulse, 0.f, m_maxImpulse);
    if (m_jumpImpulse == m_maxImpulse)
    {
        TransformComponent& arrowTransform = m_arrow->GetComponent<TransformComponent>();
        XMFLOAT3 impulse = arrowTransform.GetWorldForward();
        Jump(impulse);
        m_arrow->SetActive(false);
        m_arrowTimer.ResetProgress();
    }
}

void Frog::Jump(XMFLOAT3 direction)
{   
    XMVECTOR vimpulse = XMLoadFloat3(&direction);
    vimpulse = XMVectorScale(vimpulse, m_jumpImpulse);

    XMFLOAT3 impulse;
    XMStoreFloat3(&impulse, vimpulse);
    m_jumpImpulse = 0.f;

    PhysicComponent& physic = GetComponent<PhysicComponent>();
    physic.AddImpulse(impulse);

    physic.m_useGravity = true;
    m_isGrounded = false;
    m_isOnWall = false;
}

void Frog::Rotate()
{
    Ecs& ecs = GetEcs();

    XMFLOAT3 impulse = { 0.f, 0.0f, 0.f };

    TransformComponent* transform = &GetComponent<TransformComponent>();
    TransformComponent* cameraTransform = nullptr;
    ecs.ForEach<CameraTag, TransformComponent>([&](uint32_t entity, CameraTag& tag, TransformComponent& transform)
        {
            cameraTransform = &transform;
        });

    if (cameraTransform == nullptr || transform == nullptr)
    {
        return;
    }

    XMFLOAT3 camForward = cameraTransform->GetWorldForward();
    camForward.y = 0.f;
    XMFLOAT3 frogForward = transform->GetWorldForward();

    XMVECTOR camForwardVect = XMLoadFloat3(&camForward);
    camForwardVect = XMVector3Normalize(camForwardVect);
    XMVECTOR frogForwardVect = XMLoadFloat3(&frogForward);
    frogForwardVect = XMVector3Normalize(frogForwardVect);

    XMVECTOR vectDiffAngles = XMVectorSubtractAngles(camForwardVect, frogForwardVect);
    XMFLOAT3 diffAngles;
    XMStoreFloat3(&diffAngles, vectDiffAngles);

    if (diffAngles.x >= PI_DIV12 || diffAngles.x <= -PI_DIV12 || diffAngles.z >= PI_DIV12 || diffAngles.z <= -PI_DIV12)
    {
        if (m_isGrounded)
        {
            impulse.y += 2.f;

            PhysicComponent& physic = GetComponent<PhysicComponent>();
            physic.AddImpulse(impulse);
            physic.m_useGravity = true;
            m_isGrounded = false;
        }
    }
}


void Frog::RotateUpdate()
{
    Ecs* ecs = &App::Get()->GetEcs();

    TransformComponent* transform = &GetComponent<TransformComponent>();
    TransformComponent* cameraTransform = nullptr;
    ecs->ForEach<CameraTag, TransformComponent>([&](uint32_t entity, CameraTag& tag, TransformComponent& transform)
        {
            cameraTransform = &transform;
        });

    if (cameraTransform == nullptr || transform == nullptr)
    {
        return;
    }

    XMFLOAT3 camForward = cameraTransform->GetWorldForward();
    XMFLOAT3 frogForward = transform->GetWorldForward();

    XMVECTOR camForwardVect = XMLoadFloat3(&camForward);
    camForwardVect = XMVector3Normalize(camForwardVect);
    XMVECTOR frogForwardVect = XMLoadFloat3(&frogForward);
    frogForwardVect = XMVector3Normalize(frogForwardVect);

    XMVECTOR vectDiffAngles = XMVectorSubtractAngles(camForwardVect, frogForwardVect);
    XMFLOAT3 diffAngles;
    XMStoreFloat3(&diffAngles, vectDiffAngles);

    if (abs(diffAngles.x) >= EPSILON || abs(diffAngles.z) >= EPSILON)
    {
        if (m_isGrounded == false)
        {
            transform->LookToWorld({ frogForward.x + diffAngles.x / 12, 0.0f, frogForward.z + diffAngles.z / 12 });
        }
    }
}

void Frog::InclineArrow()
{
    float dt = App::Get()->GetChrono().GetScaledDeltaTime();

    if (Input::IsKey(VK_CONTROL))
    {
        m_slope += dt * 0.5f;
        m_arrow->SetActive(true);
    }

    if (Input::IsKey(VK_SHIFT))
    {
        m_slope -= dt * 0.5f;
        m_arrow->SetActive(true);
    }

    m_slope = std::clamp(m_slope, -XM_PIDIV2, 0.f);
    m_arrow->SetSlope(m_slope);
}

void Frog::ControllerMove()
{
    float forward = 0.f;
    float right = 0.f;

    if (m_isGrounded)
    {
        if (Input::IsKey('Z') || Input::IsKey(VK_UP))
            forward += 1.f;

        if (Input::IsKey('S') || Input::IsKey(VK_DOWN))
            forward -= 1.f;

        if (Input::IsKey('Q') || Input::IsKey(VK_LEFT))
            right -= 1.f;

        if (Input::IsKey('D') || Input::IsKey(VK_RIGHT))
            right += 1.f;
    }

    if (forward == 0.f && right == 0.f)
        return;

    Move(forward, right);
}

void Frog::ControllerJump()
{
    if (Input::IsKeyDown(VK_SPACE))
        m_isSpacePressed = true;

    if (Input::IsKeyUp(VK_SPACE))
    {
        m_isSpacePressed = false;

        if (m_isGrounded || m_isOnWall)
        {
            TransformComponent& arrowTransform = m_arrow->GetComponent<TransformComponent>();
            XMFLOAT3 impulse = arrowTransform.GetWorldForward();
            Jump(impulse);
            m_arrow->SetActive(false);
            m_arrowTimer.ResetProgress();
        }
    }
}

void Frog::Move(float _forward, float _right)
{
    m_jumpImpulse = 2.f;

    XMVECTOR vDirection = XMLoadFloat3(&m_normal);

    TransformComponent& transform = GetComponent<TransformComponent>();
    XMFLOAT3 forward = transform.GetWorldForward();
    XMVECTOR vForward = XMLoadFloat3(&forward);
    vForward = XMVectorScale(vForward, _forward);
    vDirection = XMVectorAdd(vDirection, vForward);

    XMFLOAT3 right = transform.GetWorldRight();
    XMVECTOR vRight = XMLoadFloat3(&right);
    vRight = XMVectorScale(vRight, _right);
    vDirection = XMVectorAdd(vDirection, vRight);

    vDirection = XMVector3Normalize(vDirection);

    XMFLOAT3 direction;
    XMStoreFloat3(&direction, vDirection);
    Jump(direction);
}



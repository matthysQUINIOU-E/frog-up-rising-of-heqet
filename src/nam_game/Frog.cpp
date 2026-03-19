#include "pch.h"
#include "Frog.h"
#include "Camera.h"
#include "FrogArrow.h"

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

    Scene* scene = GetScene();
    m_arrow = &scene->CreateGameObject<FrogArrow>(false);
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

    if (m_isSpacePressed && m_isGrounded)
        ChargeJump();
}

void Frog::OnController()
{
    float forward = 0.f;
    float right = 0.f;

    float dt = App::Get()->GetChrono().GetScaledDeltaTime();

    if (Input::IsKeyDown(VK_SPACE))
        m_isSpacePressed = true;

    if (Input::IsKeyUp(VK_SPACE) )
    {
        m_isSpacePressed = false;

        if(m_isGrounded)
        {
            TransformComponent& arrowTransform = m_arrow->GetComponent<TransformComponent>();
            XMFLOAT3 impulse = arrowTransform.GetWorldForward();
            Jump(impulse);
            m_arrow->SetActive(false);
            m_arrowTimer.ResetProgress();
        }
    }

    if (m_isGrounded == false)
        return;


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

    
    if(Input::IsKey('Z') || Input::IsKey(VK_UP))
        forward += 1.f;
    
    if (Input::IsKey('S') || Input::IsKey(VK_DOWN))
        forward -= 1.f;
    
    if (Input::IsKey('Q') || Input::IsKey(VK_LEFT))
        right -= 1.f;
    
    if (Input::IsKey('D') || Input::IsKey(VK_RIGHT))
        right += 1.f;

    if (forward == 0.f && right == 0.f)
        return;
        
    Move(forward, right);
}
   

void Frog::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{
    PhysicComponent& physic = GetComponent<PhysicComponent>();

    // make this simple and bad for the proto
    // need tag to know when player collide on each other
    if (collisionInfo.m_normal.y < 0.f)
    {
        m_isGrounded = false;
        physic.m_velocity.y = 0.f;
    }
    else
    {
        m_isGrounded = true;
        physic.m_useGravity = false;
        physic.m_velocity = { 0.f,0.f,0.f };
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
}

void Frog::Move(float _forward, float _right)
{
    m_jumpImpulse = 2.f;

    XMVECTOR vDirection = { 0.f, 1.f, 0.f };

    TransformComponent& transform = GetComponent<TransformComponent>();
    XMFLOAT3 forward = transform.GetWorldForward();
    XMVECTOR vForward = XMLoadFloat3(&forward);
    vForward = XMVectorScale(vForward, _forward);
    vDirection += vForward;

    XMFLOAT3 right = transform.GetWorldRight();
    XMVECTOR vRight = XMLoadFloat3(&right);
    vRight = XMVectorScale(vRight, _right);
    vDirection += vRight;

    vDirection = XMVector3Normalize(vDirection);

    XMFLOAT3 direction;
    XMStoreFloat3(&direction, vDirection);
    Jump(direction);
}



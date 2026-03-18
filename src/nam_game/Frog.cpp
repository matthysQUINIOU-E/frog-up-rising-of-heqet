#include "pch.h"
#include "Frog.h"
#include "Camera.h"

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

    SetBoxCollider();
	SetBehavior();
    SetController();
}

void Frog::OnUpdate()
{


    if (m_isSpacePressed && m_isGrounded)
        ChargeJump();
}

void Frog::OnController()
{
    if (Input::IsKeyDown(VK_SPACE))
        m_isSpacePressed = true;

    if (Input::IsKeyUp(VK_SPACE) )
    {
        m_isSpacePressed = false;

        if(m_isGrounded)
        {
            Ecs& ecs = App::Get()->GetEcs();

            TransformComponent* cameraTransform = nullptr;
            ecs.ForEach<CameraTag, TransformComponent>([&](uint32_t entity, CameraTag& tag, TransformComponent& transform)
                {
                    cameraTransform = &transform;
                });

            if (cameraTransform == nullptr)
            {
                m_jumpImpulse = 0.f;
                return;
            }
            XMFLOAT3 impulse = cameraTransform->GetWorldForward();
            Jump(impulse);
        }
    }

    if (m_isGrounded == false)
        return;
    
    if(Input::IsKey('Z') || Input::IsKey(VK_UP))
    {
        MoveForward();
    }
    if (Input::IsKey('S') || Input::IsKey(VK_DOWN))
    {
        MoveBack();
    }
    if (Input::IsKey('Q') || Input::IsKey(VK_LEFT))
    {
        MoveLeft();
    }
    if (Input::IsKey('D') || Input::IsKey(VK_RIGHT))
    {
        MoveRight();
    }

}

void Frog::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{
    // make this simple and bad for the proto
    m_isGrounded = true;

    PhysicComponent& physic = GetComponent<PhysicComponent>();
    physic.m_velocity = { 0.f,0.f,0.f };
    physic.m_useGravity = false;
}

void Frog::ChargeJump()
{
    float dt = App::Get()->GetChrono().GetScaledDeltaTime();
    m_jumpImpulse += m_maxImpulse * dt * m_chargeJumpRate;
    m_jumpImpulse = std::clamp(m_jumpImpulse, 0.f, m_maxImpulse);
    if (m_jumpImpulse == m_maxImpulse)
    {
        Ecs& ecs = App::Get()->GetEcs();

        TransformComponent* cameraTransform = nullptr;
        ecs.ForEach<CameraTag, TransformComponent>([&](uint32_t entity, CameraTag& tag, TransformComponent& transform)
        {
            cameraTransform = &transform;
        });

        if (cameraTransform == nullptr)
        {
            m_jumpImpulse = 0.f;
            return;
        }
        XMFLOAT3 impulse = cameraTransform->GetWorldForward();
        Jump(impulse);
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

void Frog::MoveForward()
{
    m_jumpImpulse = 2.f;

    TransformComponent& transform = GetComponent<TransformComponent>();
    XMFLOAT3 forward = transform.GetWorldForward();
    forward.y += 1.f;
    Jump(forward);
}

void Frog::MoveBack()
{
    m_jumpImpulse = 2.f;

    TransformComponent& transform = GetComponent<TransformComponent>();
    XMFLOAT3 forward = transform.GetWorldForward();
    forward.y += 1.f;
    forward.z = -forward.z;
    Jump(forward);
}

void Frog::MoveLeft()
{
    m_jumpImpulse = 2.f;

    TransformComponent& transform = GetComponent<TransformComponent>();
    XMFLOAT3 right = transform.GetWorldRight();
    right.y += 1.f;
    right.x = -right.x;
    Jump(right);
}

void Frog::MoveRight()
{
    m_jumpImpulse = 2.f;

    TransformComponent& transform = GetComponent<TransformComponent>();
    XMFLOAT3 right = transform.GetWorldRight();
    right.y += 1.f;
    Jump(right);
}
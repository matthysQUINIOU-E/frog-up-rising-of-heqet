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

    if (Input::IsKeyUp(VK_SPACE))
    {
        Jump();
        m_isSpacePressed = false;
    }
}

void Frog::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{
    // make this simple and bad for the proto
    m_isGrounded = true;

    PhysicComponent& physic = GetComponent<PhysicComponent>();
    physic.m_velocity = { 0.f,0.f,0.f };
}

void Frog::ChargeJump()
{
    float dt = App::Get()->GetChrono().GetScaledDeltaTime();
    m_jumpImpulse += m_maxImpulse * dt;
    m_jumpImpulse = std::clamp(m_jumpImpulse, 0.f, m_maxImpulse);
    if (m_jumpImpulse == m_maxImpulse)
        Jump();
}

void Frog::Jump()
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
    impulse.x *= m_jumpImpulse;
    impulse.y *= m_jumpImpulse;
    impulse.z *= m_jumpImpulse;

    m_jumpImpulse = 0.f;

    PhysicComponent& physic = GetComponent<PhysicComponent>();
    physic.AddImpulse(impulse);
}

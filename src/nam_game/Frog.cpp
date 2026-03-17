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
            JumpCamera();
    }

    if (m_isGrounded == false)
        return;
    
    if(Input::IsKeyDown('Z') || Input::IsKeyDown(VK_UP))
    {
        MoveForward();
    }
    if (Input::IsKeyDown('S') || Input::IsKeyDown(VK_DOWN))
    {
        MoveBack();
    }
    if (Input::IsKeyDown('Q') || Input::IsKeyDown(VK_LEFT))
    {
        MoveLeft();
    }
    if (Input::IsKeyDown('D') || Input::IsKeyDown(VK_RIGHT))
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
        JumpCamera();
    }
}

void Frog::JumpCamera()
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

    physic.m_useGravity = true;
    m_isGrounded = false;
}

void Frog::Jump(XMFLOAT3 direction)
{   
    XMVECTOR vimpulse = XMLoadFloat3(&direction);
    XMVectorScale(vimpulse, m_jumpImpulse);

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
    m_jumpImpulse = 5.f;

    TransformComponent& transform = GetComponent<TransformComponent>();
    XMFLOAT3 forward = transform.GetWorldForward();
    forward.y += 2.f;
    Jump(forward);
}

void Frog::MoveBack()
{

}

void Frog::MoveLeft()
{

}

void Frog::MoveRight()
{

}
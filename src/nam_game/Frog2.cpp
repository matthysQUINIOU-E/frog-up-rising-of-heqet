#include "pch.h"
#include "Frog2.h"
#include "Frog1.h"
#include "ColliderTag.h"
#include "FrogTongue.h"
#include "Controller.h"
#include "GameVariables.h"
#include "MeshManager.h"

using namespace nam;
using namespace DirectX;

void Frog2::OnInit()
{
    Frog::OnInit();

    MeshRendererComponent& mrc = GetComponent<MeshRendererComponent>();
    mrc.mp_mesh = MeshManager::GetMesh(MeshTag::SmallPlatform);

    TransformComponent& tc = GetComponent<TransformComponent>();
    tc.SetWorldPosition({ 1.f,2.f,0.f });

    AddComponent<Frog2Tag>({});

    BoxColliderComponent& box = SetBoxCollider();
    box.m_tag = (size)ColliderTag::FrogEllie;
    box.m_shouldCollideWith.insert((size)ColliderTag::Platform);
    box.m_shouldCollideWith.insert((size)ColliderTag::Ground);
    box.m_shouldCollideWith.insert((size)ColliderTag::FrogJoel);
    box.m_shouldCollideWith.insert((size)ColliderTag::TongueJoel);
    box.m_shouldCollideWith.insert((size)ColliderTag::Checkpoint);
    box.m_shouldCollideWith.insert((size)ColliderTag::PressurePlate);

    Scene& scene = GetScene();
    m_tongue = &scene.CreateGameObject<FrogTongue>(false);
    TransformComponent& tongueTransform = m_tongue->GetComponent<TransformComponent>();
    tongueTransform.SetParent(&GetComponent<TransformComponent>());
    BoxColliderComponent& tongueCollider = m_tongue->GetComponent<BoxColliderComponent>();
    tongueCollider.m_tag = (size)ColliderTag::TongueEllie;
    tongueCollider.m_shouldCollideWith.insert((size)ColliderTag::FrogJoel);
    m_tongue->SetFrog(this);

    SetBehavior();
    SetController();

    m_maxImpulse = 25.f;
}

void Frog2::OnUpdate()
{
    TransformComponent* transform = &GetComponent<TransformComponent>();
    XMFLOAT3 frogForward = transform->GetWorldForward();

    transform->LookToWorld({ frogForward.x, 0.0f, frogForward.z });

    Frog::OnUpdate();
}

void Frog2::OnController()
{
    if (GameVariables::s_isGamePaused)
        return;

    if (Controller::Get(ControlType::SwitchFrog1))
        m_isFrogActive = false;

    if (Controller::Get(ControlType::SwitchFrog2))
        m_isFrogActive = true;

    Frog::OnController();

    Swallow& swallow = GetComponent<Swallow>();
    if (Input::IsKeyDown('F') && swallow.m_hasSwallowed && m_isGrounded)
    {
        SpitOut();
    }
}

void Frog2::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
    Frog::OnCollision(self, other);

    PhysicComponent& physic = GetComponent<PhysicComponent>();


    bool onFrog = (other.m_tag == (size)ColliderTag::FrogJoel) && self.m_normal.y < 0.f;

    if(onFrog)
    {
        m_isGrounded = true;
        m_isorientedGround = true;
        physic.m_useGravity = false;
        physic.m_velocity = { 0.f,0.f,0.f };
    }
    
    if (other.m_tag == (size)ColliderTag::TongueJoel)
    {
        IsSwallowed();
    }

}

void Frog2::IsSwallowed()
{
    if (CheckComponent<Frog1Tag>() == false)
        return;

    TransformComponent& transform = GetComponent<TransformComponent>();
    Swallow& swallow = GetComponent<Swallow>();
    BoxColliderComponent& box = GetComponent<BoxColliderComponent>();
    PhysicComponent& pc = GetComponent<PhysicComponent>();

    box.m_shouldCollideWith.erase((size)ColliderTag::FrogJoel);
    box.m_shouldCollideWith.erase((size)ColliderTag::TongueJoel);
    transform.SetWorldScale({ 0.01f, 0.01f, 0.01f });
    transform.SetWorldPosition(m_otherFrogTransform->GetWorldPosition());
    pc.m_useGravity = false;
    swallow.m_isSwallowed = true;
}

void Frog2::SpitOut()
{
    if (CheckComponent<Frog1Tag>() == false)
        return;

    TransformComponent& transform = GetComponent<TransformComponent>();
    Swallow& swallow = GetComponent<Swallow>();
   
    float offset = 3.f;
    XMFLOAT3 posFrog1 = transform.GetWorldPosition();
    XMFLOAT3 forwardFrog1 = transform.GetWorldForward();
    XMFLOAT3 newPos = { posFrog1.x + (forwardFrog1.x * offset), posFrog1.y + forwardFrog1.y, posFrog1.z + (forwardFrog1.z * offset) };
    m_otherFrogTransform->SetWorldPosition(newPos);
    m_otherFrogTransform->SetWorldScale({ 1.f, 1.f, 1.f });
    swallow.m_hasSwallowed = false;

    m_otherFrogCollider->m_shouldCollideWith.insert((size)ColliderTag::FrogEllie);
    m_otherFrogCollider->m_shouldCollideWith.insert((size)ColliderTag::TongueEllie);
    m_otherFrogPhysic->m_useGravity = true;
}

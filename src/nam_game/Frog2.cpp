#include "pch.h"
#include "Frog2.h"
#include "ColliderTag.h"
#include "FrogTongue.h"
#include "Controller.h"

using namespace nam;
using namespace DirectX;

void Frog2::OnInit()
{
    Frog::OnInit();

    MeshRendererComponent& mrc = GetComponent<MeshRendererComponent>();
    mrc.mp_mesh->SetColor({ 0.0f ,0.0f ,0.5f ,1.f });

    TransformComponent& tc = GetComponent<TransformComponent>();
    tc.SetWorldPosition({ 1.f,2.f,0.f });

    AddComponent<Frog2Tag>({});

    BoxColliderComponent& box = SetBoxCollider();
    box.m_tag = (size)ColliderTag::FrogEllie;

    SetBehavior();
    SetController();

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
    if (Controller::Get(ControlType::SwitchFrog1))
        m_isFrogActive = false;

    if (Controller::Get(ControlType::SwitchFrog2))
        m_isFrogActive = true;

    Frog::OnController();
}

void Frog2::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
    Frog::OnCollision(self, other);

    PhysicComponent& physic = GetComponent<PhysicComponent>();

    bool onFrog = (other.m_tag == (size)ColliderTag::FrogJoel) && self.m_normal.y < 0.f;

    if(onFrog)
    {
        m_isGrounded = true;
        physic.m_useGravity = false;
        physic.m_velocity = { 0.f,0.f,0.f };
    }
}

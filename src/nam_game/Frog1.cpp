#include "pch.h"
#include "Frog1.h"
#include "ColliderTag.h"

using namespace nam;
using namespace DirectX;

void Frog1::OnInit()
{
    Frog::OnInit();

    MeshRendererComponent& mrc = GetComponent<MeshRendererComponent>();
    mrc.mp_mesh->SetColor({ 0.5f, 0.0f, 0.0f, 1.f });
        
    TransformComponent& tc = GetComponent<TransformComponent>();
    tc.SetWorldPosition({ -1.f,2.f,0.f });

    AddComponent<Frog1Tag>({});

    BoxColliderComponent& box = SetBoxCollider();
    box.m_tag = (size)ColliderTag::FrogJoel;

    SetBehavior();
    SetController();

    m_isFrogActive = true;
}

void Frog1::OnUpdate()
{
    if (m_isFrogActive)
        Frog::OnUpdate();
}

void Frog1::OnController()
{
    if (Input::IsKeyDown('1'))
        m_isFrogActive = true;

    if (Input::IsKeyDown('2'))
        m_isFrogActive = false;

    if (m_isFrogActive)
        Frog::OnController();
}

void Frog1::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{
    Frog::OnCollision(self, other, collisionInfo);

    PhysicComponent& physic = GetComponent<PhysicComponent>();

    bool onFrog = (collisionInfo.m_tag2 == (size)ColliderTag::FrogEllie) && collisionInfo.m_normal.y < 0.f;
    
    if (onFrog)
    {
        m_isGrounded = true;
        physic.m_useGravity = false;
        physic.m_velocity = { 0.f,0.f,0.f };
    }

   
}

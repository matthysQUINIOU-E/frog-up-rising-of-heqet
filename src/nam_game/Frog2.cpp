#include "pch.h"
#include "Frog2.h"

using namespace nam;
using namespace DirectX;

void Frog2::OnInit()
{
    MeshRendererComponent mrc;
    mrc.CreateMeshInstance();
    mrc.mp_mesh->BuildBox({ 1.f,1.f, 1.f }, { 0.0f,0.0f,0.5f,1.f });
    AddComponent<MeshRendererComponent>(mrc);

    TransformComponent tc;
    tc.SetWorldPosition({ 1.f,2.f,0.f });
    AddComponent<TransformComponent>(tc);

    AddComponent<PhysicComponent>(PhysicComponent());
    AddComponent<Frog2Tag>({});

    SetBoxCollider();
    SetBehavior();
    SetController();
}

void Frog2::OnUpdate()
{
    if (m_isFrogActive)
        Frog::OnUpdate();
}

void Frog2::OnController()
{
    if (Input::IsKeyDown('1'))
        m_isFrogActive = false;

    if (Input::IsKeyDown('2'))
        m_isFrogActive = true;

    if (m_isFrogActive)
        Frog::OnController();
}

void Frog2::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{
    Frog::OnCollision(self, other, collisionInfo);
}

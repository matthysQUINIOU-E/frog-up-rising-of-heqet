#include "pch.h"
#include "Checkpoint.h"
#include "Frog.h"
#include "ColliderTag.h"

using namespace nam;
using namespace DirectX;

void Checkpoint::OnInit()
{
    TransformComponent tc;
    AddComponent<TransformComponent>(tc);

    MeshRendererComponent mrc;
    mrc.CreateMeshInstance();
    mrc.mp_mesh->BuildPlane({ 3.f, 3.f }, { 1.f, 0.f, 0.f, 1.f });
    AddComponent<MeshRendererComponent>(mrc);

    BoxColliderComponent& box = SetBoxCollider();
    box.m_tag = (size)ColliderTag::Checkpoint;
    box.m_noIntersectionPush = true;
    AddComponent<BoxColliderComponent>(box);
}

void Checkpoint::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
}
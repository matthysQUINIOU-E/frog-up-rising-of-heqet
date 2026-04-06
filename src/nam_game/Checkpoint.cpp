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
    mrc.mp_mesh->BuildPlane({ 3.f, 3.f }, { 1.f, 0.f, 0.f, 0.f });
    AddComponent<MeshRendererComponent>(mrc);

    BoxColliderComponent& box = SetBoxCollider();
    box.m_tag = (size)ColliderTag::Checkpoint;
    AddComponent<BoxColliderComponent>(box);
}

void Checkpoint::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
    if (other.m_tag != (size)ColliderTag::FrogEllie || other.m_tag != (size)ColliderTag::FrogJoel)
        return;

    TransformComponent& transform = GetComponent<TransformComponent>();
    m_center = transform.GetWorldPosition();

    //Frog* frog = static_cast<Frog*>(/*COMMENT JE RECUPERE MA PTN DE GRNOUILLE AVEC L'ID*/other.m_entity);
    //if (frog)
    //    frog->SetCheckpoint(m_center);
}
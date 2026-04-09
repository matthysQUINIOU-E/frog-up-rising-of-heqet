#include "pch.h"
#include "Checkpoint.h"
#include "Frog.h"
#include "ColliderTag.h"
#include <SceneTag.h>

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
    if ((other.m_tag == (size)ColliderTag::FrogEllie || other.m_tag == (size)ColliderTag::FrogJoel) && m_levelEnd)
    {
        App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Gameplay).SetActive(false);
        App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Victory).SetActive(true);
        Input::ShowMouse();
    }
}

void Checkpoint::SetLevelEnd(bool end)
{
    m_levelEnd = end;
}

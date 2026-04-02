#include "pch.h"
#include "Collectible.h"
#include "ColliderTag.h"

using namespace nam;
using namespace DirectX;

void Collectible::SetColor(const DirectX::XMFLOAT4& color)
{
    MeshRendererComponent& mrc = GetComponent<MeshRendererComponent>();
	mrc.mp_mesh->SetColor(color);
}

void Collectible::OnInit()
{
    MeshRendererComponent mrc;
    mrc.CreateMeshInstance();
	mrc.mp_mesh->BuildIcoSphere(0.5f, 3, { 1.f,0.84f,0.f,1.f });
    AddComponent<MeshRendererComponent>(mrc);

    TransformComponent tc;
    AddComponent<TransformComponent>(tc);

	SetBehavior();
	BoxColliderComponent& box = SetBoxCollider();
	box.m_tag = (size)ColliderTag::Collectible;
	box.m_shouldCollideWith.insert((size)ColliderTag::FrogEllie);
	box.m_shouldCollideWith.insert((size)ColliderTag::FrogJoel);
}

void Collectible::OnUpdate()
{
	TransformComponent& transform = GetComponent<TransformComponent>();
    transform.RotateAroundWorld(transform.GetWorldPosition(), { 0.f,1.f,0.f }, 0.01f);
}

void Collectible::OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other)
{
    SetActive(false);
}

void Collectible::SetPosition(XMFLOAT3 pos)
{
    TransformComponent& transform = GetComponent<TransformComponent>();
    transform.SetWorldPosition(pos);
}

#include "pch.h"
#include "Collectible.h"
#include "ColliderTag.h"

void Collectible::SetColor(XMFLOAT4 _color)
{
	MeshRendererComponent cm = GetComponent<MeshRendererComponent>();
	cm.mp_mesh->BuildIcoSphere(1.0f, 3, _color);
}

void Collectible::OnInit()
{
	MeshRendererComponent cm;
	cm.CreateMeshInstance();
	AddComponent<MeshRendererComponent>(cm);

	TransformComponent ct;
	AddComponent<TransformComponent>(ct);

	BoxColliderComponent& cc = SetBoxCollider();
	cc.m_tag = (size)ColliderTag::Collectible;
	cc.m_shouldCollideWith.insert((size)ColliderTag::FrogJoel);
	cc.m_shouldCollideWith.insert((size)ColliderTag::FrogEllie);
	cc.m_shouldCollideWith.insert((size)ColliderTag::Tongue);
	cc.m_noIntersectionPush = true;

	SetBehavior();
}

void Collectible::OnUpdate()
{
	TransformComponent ct = GetComponent<TransformComponent>();
	ct.RotateLocalAroundAxis(ct.GetWorldPosition(), 15.f);
}

void Collectible::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
	SetActive(false);
}

void Collectible::SetPosition(XMFLOAT3 _pos)
{
	TransformComponent ct = GetComponent<TransformComponent>();
	ct.SetWorldPosition(_pos);
}

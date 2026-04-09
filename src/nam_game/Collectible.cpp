#include "pch.h"
#include "Collectible.h"
#include "ColliderTag.h"

void Collectible::SetColor(XMFLOAT4 _color)
{
	MeshRendererComponent cm = GetComponent<MeshRendererComponent>();
	cm.mp_mesh->BuildIcoSphere(0.5f, 3, _color);
}

void Collectible::OnInit()
{
	MeshRendererComponent cm;
	cm.CreateMeshInstance();
	AddComponent<MeshRendererComponent>(cm);

	TransformComponent ct;
	AddComponent<TransformComponent>(ct);

	SetBehavior();
}

void Collectible::OnUpdate()
{
	TransformComponent ct = GetComponent<TransformComponent>();
	//ct.RotateWorldAroundAxis(ct.GetWorldPosition(), 15.f);
}

void Collectible::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
	SetActive(false);
}

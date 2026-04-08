#include "pch.h"
#include "Grasshopper.h"
#include "ColliderTag.h"

void Grasshopper::OnInit()
{
	Collectible::OnInit();
	SetColor({ 0.5f, 0.75f, 0.35f, 1.0f });

	BoxColliderComponent& cc = SetBoxCollider();
	cc.m_tag = (size)ColliderTag::CollectGras;
	cc.m_shouldCollideWith.insert((size)ColliderTag::FrogJoel);
	cc.m_shouldCollideWith.insert((size)ColliderTag::FrogEllie);
	cc.m_shouldCollideWith.insert((size)ColliderTag::Tongue);
	cc.m_noIntersectionPush = true;
}

void Grasshopper::OnUpdate()
{
	Collectible::OnUpdate();
}

void Grasshopper::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
	Collectible::OnCollision(self, other);
}

#include "pch.h"
#include "Dragonfly.h"
#include "ColliderTag.h"

void Dragonfly::OnInit()
{
	Collectible::OnInit();
	SetColor({ 0.35f, 0.2f, 0.5f, 1.0f });

	BoxColliderComponent& cc = SetBoxCollider();
	cc.m_tag = (size)ColliderTag::CollectDrag;
	cc.m_shouldCollideWith.insert((size)ColliderTag::FrogJoel);
	cc.m_shouldCollideWith.insert((size)ColliderTag::FrogEllie);
	cc.m_shouldCollideWith.insert((size)ColliderTag::Tongue);
	cc.m_noIntersectionPush = true;
}

void Dragonfly::OnUpdate()
{
	Collectible::OnUpdate();
}

void Dragonfly::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
	Collectible::OnCollision(self, other);
}

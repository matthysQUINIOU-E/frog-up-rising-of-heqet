#include "pch.h"
#include "Spider.h"
#include "ColliderTag.h"

void Spider::OnInit()
{
	Collectible::OnInit();
	SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });

	BoxColliderComponent& cc = SetBoxCollider();
	cc.m_tag = (size)ColliderTag::CollectSpid;
	cc.m_shouldCollideWith.insert((size)ColliderTag::FrogJoel);
	cc.m_shouldCollideWith.insert((size)ColliderTag::FrogEllie);
	cc.m_shouldCollideWith.insert((size)ColliderTag::Tongue);
	cc.m_noIntersectionPush = true;
}

void Spider::OnUpdate()
{
	Collectible::OnUpdate();
}

void Spider::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
	Collectible::OnCollision(self, other);
}

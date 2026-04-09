#include "pch.h"
#include "Dragonfly.h"
#include "ColliderTag.h"

void Dragonfly::OnInit()
{
	Collectible::OnInit();
	SetColor({ 0.35f, 0.2f, 0.5f, 1.0f });
}

void Dragonfly::OnUpdate()
{
	Collectible::OnUpdate();
}

void Dragonfly::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
	Collectible::OnCollision(self, other);
}

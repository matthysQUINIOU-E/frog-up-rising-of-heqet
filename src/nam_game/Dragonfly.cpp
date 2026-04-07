#include "pch.h"
#include "Dragonfly.h"

void Dragonfly::OnInit()
{
	Collectible::OnInit();
	SetColor({ 0.0f, 0.0f, 1.0f, 1.0f });
}

void Dragonfly::OnUpdate()
{
	Collectible::OnUpdate();
}

void Dragonfly::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
	Collectible::OnCollision(self, other);
}

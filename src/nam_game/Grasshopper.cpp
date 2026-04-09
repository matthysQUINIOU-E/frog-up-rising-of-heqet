#include "pch.h"
#include "Grasshopper.h"
#include "ColliderTag.h"

void Grasshopper::OnInit()
{
	Collectible::OnInit();
	SetColor({ 0.5f, 0.75f, 0.35f, 1.0f });
}

void Grasshopper::OnUpdate()
{
	Collectible::OnUpdate();
}

void Grasshopper::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
	Collectible::OnCollision(self, other);
}

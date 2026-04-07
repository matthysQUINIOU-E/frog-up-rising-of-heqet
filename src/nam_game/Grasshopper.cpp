#include "pch.h"
#include "Grasshopper.h"

void Grasshopper::OnInit()
{
	Collectible::OnInit();
	SetColor({ 0.0f, 1.0f, 0.0f, 1.0f });
}

void Grasshopper::OnUpdate()
{
	Collectible::OnUpdate();
}

void Grasshopper::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
	Collectible::OnCollision(self, other);
}

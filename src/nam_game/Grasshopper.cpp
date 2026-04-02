#include "pch.h"
#include "Grasshopper.h"

void Grasshopper::OnInit()
{
	Collectible::OnInit();
	SetColor({ 0.f,1.f,0.f,1.f });
}

void Grasshopper::OnUpdate()
{
	Collectible::OnUpdate();
}

void Grasshopper::OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other)
{
	Collectible::OnCollision(self, other);
}

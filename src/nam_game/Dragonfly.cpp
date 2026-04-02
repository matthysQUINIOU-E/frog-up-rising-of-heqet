#include "pch.h"
#include "Dragonfly.h"
#include "ColliderTag.h"

void Dragonfly::OnInit()
{
	Collectible::OnInit();
	SetColor({ 0.5294117647058824f,0.803921568627451f,0.9215686274509804f,1.f });
}

void Dragonfly::OnUpdate()
{
	Collectible::OnUpdate();
}

void Dragonfly::OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other)
{
	Collectible::OnCollision(self, other);
}

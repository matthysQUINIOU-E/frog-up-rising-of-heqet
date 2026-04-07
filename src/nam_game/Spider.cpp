#include "pch.h"
#include "Spider.h"

void Spider::OnInit()
{
	Collectible::OnInit();
	SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
}

void Spider::OnUpdate()
{
	Collectible::OnUpdate();
}

void Spider::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
	Collectible::OnCollision(self, other);
}

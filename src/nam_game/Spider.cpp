#include "pch.h"
#include "Spider.h"

void Spider::OnInit()
{
	Collectible::OnInit();
	SetColor({ 0.6470588235294118f,0.1647058823529412f,0.1647058823529412f,1.f });
}

void Spider::OnUpdate()
{
	Collectible::OnUpdate();
}

void Spider::OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other)
{
	Collectible::OnCollision(self, other);
}

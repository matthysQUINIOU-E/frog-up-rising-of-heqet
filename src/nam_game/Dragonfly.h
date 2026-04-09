#pragma once
#include "Collectible.h"

class Dragonfly : public Collectible
{
public:
	void OnInit() override;
	void OnUpdate() override;
	void OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other) override;
};


#pragma once
#include "Collectible.h"

class Dragonfly : public Collectible
{
public:
	void OnInit() override;
	void OnUpdate() override;
	void OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other) override;
};


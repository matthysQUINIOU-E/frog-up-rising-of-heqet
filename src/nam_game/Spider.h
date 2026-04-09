#pragma once
#include "Collectible.h"

class Spider : public Collectible
{
public:
	void OnInit() override;
	void OnUpdate() override;
	void OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other) override;
};


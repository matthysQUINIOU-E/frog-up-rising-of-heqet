#pragma once
#include "Frog.h"

class Frog1 : public Frog
{
public:
	void OnInit() override;
	void OnUpdate() override;
	void OnController() override;
	void OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other) override;
private:
	void MoveWall(float _forward, float _right);
};



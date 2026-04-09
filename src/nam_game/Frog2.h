#pragma once
#include "Frog.h"
struct Frog2Tag {};

class Frog1;

class Frog2 : public Frog
{
public:
	void OnInit() override;
	void OnUpdate() override;
	void OnController() override;
	void OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other) override;
private:
	void IsSwallowed() override;
	void SpitOut() override;
};


#pragma once

class Collectible : public nam::GameObject
{
public:
	void OnInit() override;
	void OnUpdate() override;
	void OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other) override;

};


#pragma once
class Platform : public nam::GameObject
{
public:
	void OnInit() override;
	void OnUpdate() override;
	void OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other) override;
};


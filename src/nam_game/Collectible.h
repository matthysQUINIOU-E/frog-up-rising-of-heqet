#pragma once

class Collectible : public nam::GameObject
{
public:
	void OnInit() override;
	void OnUpdate() override;
	void OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other) override;

	void SetPosition(DirectX::XMFLOAT3 position);
private:
	
};


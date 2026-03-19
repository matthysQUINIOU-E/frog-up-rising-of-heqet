#pragma once
struct Frog1Tag {};
struct Frog2Tag {};

class Frog : public nam::GameObject
{
protected:
	bool m_isFrogActive = false;
	bool m_isSpacePressed = false;
	bool m_isGrounded = false;
	bool m_isRotate = false;
	float m_jumpImpulse = 0.f;
	float m_maxImpulse = 15.f;
	float m_chargeJumpRate = 5.f;
public:
	void OnInit() override;
	void OnUpdate() override;
	void OnController() override;
	void OnCollision(nam::u32 self, nam::u32 other, const nam::CollisionInfo& collisionInfo) override;
private:
	void ChargeJump();
	void Jump(DirectX::XMFLOAT3 direction);

	void Rotate();
	void Move(float _forward, float _right);
};


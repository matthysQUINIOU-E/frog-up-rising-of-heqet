#pragma once
struct Frog1Tag {};
struct Frog2Tag {};

class Timer;
class FrogArrow;

class Frog : public nam::GameObject
{
protected:
	bool m_isFrogActive = false;
	bool m_isSpacePressed = false;
	bool m_isGrounded = false;
	bool m_isOnWall = false;
	bool m_isOrientedWall = false;
	bool m_isRotate = false;

	float m_jumpImpulse = 0.f;
	float m_maxImpulse = 15.f;
	float m_chargeJumpRate = 5.f;

	FrogArrow* m_arrow = nullptr;
	float m_targetTime = 1.5f;
	float m_slope = 0.f;
	nam::Timer m_arrowTimer;

	DirectX::XMFLOAT3 m_gravity = { 0.f, -1.f, 0.f };
	DirectX::XMFLOAT3 m_normal = { 0.f, 0.f, 0.f };

protected:
	void Jump(DirectX::XMFLOAT3 direction);
public:
	void OnInit() override;
	void OnUpdate() override;
	void OnController() override;
	void OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other) override;
private:
	void ChargeJump();
	void Move(float _forward, float _right);

	void Rotate();
	void RotateUpdate();

	void InclineArrow();
	void ControllerMove();
	void ControllerJump();
};

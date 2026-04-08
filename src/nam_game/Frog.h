#pragma once

class Timer;
class FrogArrow;
class FrogTongue;
struct Swallow;

class Frog : public nam::GameObject
{
protected:
	bool m_isFrogActive = false;
	bool m_isSpacePressed = false;
	bool m_isGrounded = false;
	bool m_isorientedGround = false;
	bool m_isOnWall = false;
	bool m_isOrientedWall = false;
	bool m_isRotate = false;
	bool m_isFiring = false;

	float m_jumpImpulse = 0.f;
	float m_maxImpulse = 15.f;
	float m_chargeJumpRate = 5.f;

	FrogArrow* m_arrow = nullptr;
	float m_targetTimeArrow = 1.5f;
	float m_slope = 0.f;
	nam::Timer m_arrowTimer;

	nam::Timer m_stompedTimer;
	float m_targetTimeStomped = 10.f;
	bool m_isStompted = false;
	DirectX::XMFLOAT3 m_stompedScale = {1.5f,0.3f,1.5f};

	nam::size m_unstompSteps = 100;
	float m_unstompStepDuration = 0.01f;
	std::vector<DirectX::XMFLOAT3> m_unstompScales;
	nam::Timer m_unstompTimer;

	DirectX::XMFLOAT3 m_gravity = { 0.f, -1.f, 0.f };
	DirectX::XMFLOAT3 m_normal = { 0.f, 0.f, 0.f };
	DirectX::XMFLOAT3 m_baseScale = { 1.f,1.f,1.f };
	
	FrogTongue* m_tongue = nullptr;

	DirectX::XMFLOAT3 m_checkpointCenter = { 0.f, 1.f, 0.f };
	bool m_hasCheckpoint = true;

	float m_gravityTimerTarget = 0.f;
	nam::Timer m_gravityTimer;

	nam::TransformComponent* m_otherFrogTransform = nullptr;
	nam::BoxColliderComponent* m_otherFrogCollider = nullptr;
	nam::PhysicComponent* m_otherFrogPhysic = nullptr;
	Swallow* m_otherFrogSwallow = nullptr;

protected:
	void Jump(DirectX::XMFLOAT3 direction);
	virtual void SpitOut();
	virtual void IsSwallowed();

	template<typename TagFrog>
	bool CheckComponent();

public:
	void OnInit() override;
	void OnUpdate() override;
	void OnController() override;
	void OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other) override;
	void SetCheckpoint(DirectX::XMFLOAT3 center);
	void Respawn();
private:
	void ChargeJump();
	void Move(float _forward, float _right);

	void Rotate();
	void RotateUpdate();

	void InclineArrow();
	void ControllerMove();
	void ControllerJump();
	void ControllerTongue();
	void ControllerGroundPound();

	void FloorWallCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other);
	void FrogCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other);

	void UseGravity(DirectX::XMFLOAT3 normal);
};

#include "Frog.inl"
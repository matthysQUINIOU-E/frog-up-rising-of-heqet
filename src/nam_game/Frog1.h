#pragma once
#include "Frog.h"

class Jauge;

class Frog1 : public Frog
{
public:
	void OnInit() override;
	void OnUpdate() override;
	void OnController() override;
	void OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other) override;
private:
	void MoveWall(float _forward, float _right);
	void ControllerMoveWall();
	void CollisionOnWall(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other);
	void UpdateJaugeDisplay(float progress);
private:
	Jauge* m_jauge = nullptr;
	nam::Timer m_jaugeTimer;
	float m_jaugeTimerTarget = 15.f;

	float m_jaugeProgress = 0.f;
	bool m_isRecharging = false;
	float m_rechargeRate = 10.f;
};



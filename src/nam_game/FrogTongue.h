#pragma once
class FrogTongue : public nam::GameObject
{
public:
	void OnInit() override;
	void OnUpdate() override;
	void OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other) override;
	
	void SetFire(bool _fire, Frog _frog);
	bool IsArrived() { return m_arrived; }
private:
	bool m_isFiring = false;
	bool m_arrived = false;
	float m_move = 0.0f;
	float m_speed = 90.f; // with deltatime x45, base speed 2.0f
	float m_maxDistance = 30.f;
	DirectX::XMFLOAT3 m_pos;
	Frog m_frog;
};


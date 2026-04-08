#pragma once
class PressurePlate : public nam::GameObject
{
private:
	uint32_t m_eventId = 0;
	bool m_isPressed = false;

	bool m_toggleMode = true;

	nam::Timer m_timerCanToggleDelay;
	float m_timerCanToggleDelayTarget = 1.f;
	bool m_canToggle = true;

	nam::Timer m_timerUpDelay; 
	float m_timerUpDelayTarget = 1.f;

	DirectX::XMFLOAT3 m_pushedScale = { 1,0.4f,1 };

public:
	void OnInit() override;
	void OnUpdate() override;
	void OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other) override;

	uint32_t GetEventId();
	void SetToggleMode(bool toggleMode);
	void SetPosition(DirectX::XMFLOAT3 position);
};


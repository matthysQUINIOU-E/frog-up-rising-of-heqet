#pragma once
class PressurePlate : public nam::GameObject
{
private:
	uint32_t m_eventId = 0;
public:
	void OnInit() override;
	void OnUpdate() override;
	void OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other) override;

	uint32_t GetEventId();
};


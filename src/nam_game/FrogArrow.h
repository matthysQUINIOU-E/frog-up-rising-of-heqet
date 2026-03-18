#pragma once
class FrogArrow : public nam::GameObject
{
public:
	void OnInit() override;

	void SetSlope(float slope);
private:
	float m_slope = 0.f;
	float m_maxSlope = DirectX::XM_PIDIV2;
};


#pragma once
class FrogArrow : public nam::GameObject
{
public:
	void OnInit() override;

	void SetSlope(float slope);
private:
	float m_slope = -DirectX::XM_PIDIV2;
	float m_maxSlope = 0.f;
};


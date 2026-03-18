#pragma once
class FrogArrow : public nam::GameObject
{
public:
	void OnInit() override;

	void SetSlope(float slope);
	void UpdateSlope(float slope);
private:
	float m_slope;
	float m_maxSlope = DirectX::XM_PIDIV2;
};


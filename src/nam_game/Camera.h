#pragma once

struct CameraTag {};

class Camera : public nam::GameObject
{
private:
	int m_frogToFollow = 0;
	DirectX::XMFLOAT3 m_targetToFollow = { 0.f,0.f,0.f };
	float m_distanceFromTarget = 5.f;
	bool m_cursorUse = false;
	float m_sensitivity = 0.001f;

public:
	void OnInit() override;
	void OnUpdate() override;
	void OnController() override;
};


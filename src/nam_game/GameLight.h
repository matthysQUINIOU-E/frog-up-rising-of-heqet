#pragma once
class GameLight : public nam::GameObject
{
public:
	void OnInit() override;
	void OnDestroy() override;
	void SetToDirectional(float intensity, DirectX::XMFLOAT3 direction, DirectX::XMFLOAT3 color);
	void SetToPoint(float intensity, DirectX::XMFLOAT3 position, float range, DirectX::XMFLOAT3 color);
	void SetToSpot(float intensity, DirectX::XMFLOAT3 position, float range, DirectX::XMFLOAT3 direction, float beginAngleRad, float endAngleRad, DirectX::XMFLOAT3 color);
};


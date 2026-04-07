#include "pch.h"

using namespace nam;
using namespace DirectX;

class Collectible : public GameObject
{
protected:
	void SetColor(XMFLOAT4 _color);
public:
	void OnInit() override;
	void OnUpdate() override;
	void OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other) override;

	void SetPosition(XMFLOAT3 _pos);
};
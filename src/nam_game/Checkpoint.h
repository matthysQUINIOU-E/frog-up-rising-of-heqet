#pragma once

class Checkpoint : public nam::GameObject
{
public:
    void OnInit() override;
    void OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other) override;
    void SetLevelEnd(bool end);
private:
    DirectX::XMFLOAT3 m_center = { 0.f, 0.f, 0.f };
    bool m_levelEnd = false;
};


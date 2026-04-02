#include "pch.h"
#include "PhysicComponent.h"

using namespace DirectX;

namespace nam
{
    void PhysicComponent::AddImpulse(const XMFLOAT3& impulse)
    {
        XMVECTOR vImpulse = XMLoadFloat3(&impulse);
        XMVECTOR vVelocity = XMLoadFloat3(&m_velocity);
        vImpulse = XMVectorScale(vImpulse, m_invMass);
        vVelocity += vImpulse;

        XMStoreFloat3(&m_velocity, vVelocity);
    }

    void PhysicComponent::SetMass(float _mass)
    {
        m_mass = _mass;
        m_invMass = 1.f / _mass;
    }
}

#include "pch.h"
#include "Frog1.h"
#include "ColliderTag.h"

using namespace nam;
using namespace DirectX;

void Frog1::OnInit()
{
    Frog::OnInit();

    MeshRendererComponent& mrc = GetComponent<MeshRendererComponent>();
    mrc.mp_mesh->SetColor({ 0.5f, 0.0f, 0.0f, 1.f });
        
    TransformComponent& tc = GetComponent<TransformComponent>();
    tc.SetWorldPosition({ -1.f,2.f,0.f });

    AddComponent<Frog1Tag>({});

    BoxColliderComponent& box = SetBoxCollider();
    box.m_tag = (size)ColliderTag::FrogJoel;

    SetBehavior();
    SetController();

    m_isFrogActive = true;
}

void Frog1::OnUpdate()
{
    if (m_isFrogActive)
        Frog::OnUpdate();
}

void Frog1::OnController()
{
    if (Input::IsKeyDown('1'))
        m_isFrogActive = true;

    if (Input::IsKeyDown('2'))
        m_isFrogActive = false;

    if (m_isOnWall && !m_isSpacePressed && Input::IsKeyUp(VK_SPACE))
    {
        PhysicComponent& physic = GetComponent<PhysicComponent>();
        physic.m_dirGravity = m_gravity; 
        m_isOnWall = false;
    }

    if (m_isFrogActive)
        Frog::OnController();

    float forward = 0.f;
    float right = 0.f;

    if(m_isOnWall)
    {
        if (Input::IsKey('Z') || Input::IsKey(VK_UP))
            forward += 1.f;

        if (Input::IsKey('S') || Input::IsKey(VK_DOWN))
            forward -= 1.f;

        if (Input::IsKey('Q') || Input::IsKey(VK_LEFT))
            right -= 1.f;

        if (Input::IsKey('D') || Input::IsKey(VK_RIGHT))
            right += 1.f;
    }

    if (forward == 0.f && right == 0.f)
        return;

    MoveWall(forward, right);
}

void Frog1::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
    Frog::OnCollision(self, other);
    PhysicComponent& physic = GetComponent<PhysicComponent>();
    TransformComponent& transform = GetComponent<TransformComponent>();


    bool onFrog = (other.m_tag == (size)ColliderTag::FrogEllie) && self.m_normal.y < 0.f;
    m_isOnWall = self.m_normal.y == 0.f;

    if (onFrog)
    {
        m_isGrounded = true;
        m_isOnWall = false;
        physic.m_useGravity = false;
        physic.m_velocity = { 0.f,0.f,0.f };
    }
    else if (m_isOnWall)
    {
        m_isGrounded = false;
        m_wallNormal = self.m_normal;
        physic.m_dirGravity = self.m_normal;
        physic.m_velocity = { 0.f,0.f,0.f };
        transform.SetWorldYPR(0.f, -XM_PIDIV2, -XM_PIDIV2);
    }
}

void Frog1::MoveWall(float _forward, float _right)
{
    m_jumpImpulse = 2.f;

    TransformComponent& transform = GetComponent<TransformComponent>();

    XMVECTOR vDirection = XMLoadFloat3(&m_wallNormal);

    XMFLOAT3 forward = transform.GetWorldForward();
    XMVECTOR vForward = XMLoadFloat3(&forward);
    vForward = XMVectorScale(vForward, _forward);
    vDirection = XMVectorAdd(vDirection, vForward);

    XMFLOAT3 right = transform.GetWorldRight();
    XMVECTOR vRight = XMLoadFloat3(&right);
    vRight = XMVectorScale(vRight, _right);
    vDirection = XMVectorAdd(vDirection, vRight);

    vDirection = XMVector3Normalize(vDirection);

    XMFLOAT3 direction;
    XMStoreFloat3(&direction, vDirection);
    Frog::Jump(direction);
}


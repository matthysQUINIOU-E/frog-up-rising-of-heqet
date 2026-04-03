#include "pch.h"
#include "Frog1.h"
#include "ColliderTag.h"
#include "Camera.h"
#include "Constant.h"
#include "SpriteManager.h"
#include "Jauge.h"


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
    box.m_shouldCollideWith.insert((size)ColliderTag::Platform);
    box.m_shouldCollideWith.insert((size)ColliderTag::FrogEllie);

    Scene& scene = GetScene();
    m_jauge = &scene.CreateGameObject<Jauge>();
    m_jaugeTimer.Init(m_jaugeTimerTarget, true);

    SetBehavior();
    SetController();

    m_isFrogActive = true;
}

void Frog1::OnUpdate()
{
    float dt = App::Get()->GetChrono().GetScaledDeltaTime();
    PhysicComponent& pc = GetComponent<PhysicComponent>();

    if (m_isFrogActive)
        Frog::OnUpdate();

    if (m_isOrientedWall)
    {
        m_jaugeTimer.Update(dt);
        m_jauge->SetActive(true);

        float time = m_jaugeTimer.GetProgress();

        float baseInterval = m_jaugeTimerTarget * 0.2f;
        float interval1 = baseInterval * 4.f;
        float interval2 = baseInterval * 3.f;
        float interval3 = baseInterval * 2.f;
        float interval4 = baseInterval;

        bool jauge5 = time >= interval1 && time < m_jaugeTimerTarget;
        bool jauge4 = time >= interval2 && time < interval1;
        bool jauge3 = time >= interval3 && time < interval2;
        bool jauge2 = time >= interval4 && time < interval3;
        bool jauge1 = time > 0.f && time < interval4;

        if (jauge5)
            m_jauge->SetJauge(JaugeType::Jauge5);
        else if (jauge4)
            m_jauge->SetJauge(JaugeType::Jauge4);
        else if (jauge3)
            m_jauge->SetJauge(JaugeType::Jauge3);
        else if (jauge2)
            m_jauge->SetJauge(JaugeType::Jauge2);
        else if (jauge1)
            m_jauge->SetJauge(JaugeType::Jauge1);
        else if (m_jaugeTimer.IsTargetReached())
        {
            m_jauge->SetJauge(JaugeType::Jauge0);
            pc.m_dirGravity = m_gravity;
        }
        

        // faire des verif avec GetProgress
    }
    else
    {
        m_jauge->SetActive(false);
        m_jaugeTimer.ResetProgress();
        m_jauge->SetJauge(JaugeType::Jauge5);
    }
}

void Frog1::OnController()
{
    if (Input::IsKeyDown('1'))
        m_isFrogActive = true;

    if (Input::IsKeyDown('2'))
        m_isFrogActive = false;

    if (m_isSpacePressed) 
    {
        PhysicComponent& physic = GetComponent<PhysicComponent>();
        physic.m_dirGravity = m_gravity; 
        m_isOnWall = false;
    }

    if (m_isFrogActive)
        Frog::OnController();

    if(m_isOnWall)
        ControllerMoveWall();
}

void Frog1::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
    Frog::OnCollision(self, other);
    PhysicComponent& physic = GetComponent<PhysicComponent>();
    TransformComponent& transform = GetComponent<TransformComponent>();

    bool onFrog = (other.m_tag == (size)ColliderTag::FrogEllie) && self.m_normal.y < 0.f;
    m_isOnWall = self.m_normal.y == 0.f && (other.m_tag != (size)ColliderTag::FrogEllie);

    if (onFrog)
    {
        m_isGrounded = true;
        m_isOnWall = false;
        physic.m_useGravity = false;
        physic.m_velocity = { 0.f,0.f,0.f };
    }
    else if (m_isOnWall)
    {
        CollisionOnWall(self, other);
    }
}

void Frog1::MoveWall(float _forward, float _right)
{
    m_jumpImpulse = 2.f;

    TransformComponent& transform = GetComponent<TransformComponent>();

    XMVECTOR vDirection = XMLoadFloat3(&m_normal);

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

void Frog1::ControllerMoveWall()
{
    float forward = 0.f;
    float right = 0.f;

    if (m_isOnWall)
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

void Frog1::CollisionOnWall(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
    PhysicComponent& physic = GetComponent<PhysicComponent>();
    TransformComponent& transform = GetComponent<TransformComponent>();

    m_gravityTimer.ResetProgress();
    m_isOrientedWall = true;
    m_isGrounded = false;
    m_normal = other.m_normal;
    physic.m_dirGravity = self.m_normal;
    physic.m_velocity = { 0.f,0.f,0.f };

    XMVECTOR vNormal = XMLoadFloat3(&m_normal);

    XMFLOAT3 currentFwd = transform.GetWorldForward();
    XMVECTOR vCurrentFwd = XMLoadFloat3(&currentFwd);
    XMVECTOR vProjFwd = vCurrentFwd - XMVectorScale(vNormal, XMVectorGetX(XMVector3Dot(vCurrentFwd, vNormal)));

    float projLen = XMVectorGetX(XMVector3Length(vProjFwd));

    XMVECTOR vForward = {0.f, 0.f, 0.f};
    if (projLen > EPSILON)
    {
        vForward = XMVector3Normalize(vProjFwd);
    }
    else
    {
        XMVECTOR vGlobalUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);
        XMVECTOR vRight = XMVector3Normalize(XMVector3Cross(vGlobalUp, vNormal));

        XMVECTOR vForward = XMVector3Normalize(XMVector3Cross(vNormal, vRight));
    }

    XMFLOAT3 newForward;
    XMStoreFloat3(&newForward, vForward);
    transform.LookToWorld(newForward, m_normal);
}


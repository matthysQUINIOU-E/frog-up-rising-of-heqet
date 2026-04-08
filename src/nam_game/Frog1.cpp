#include "pch.h"
#include "Frog1.h"
#include "Frog2.h"
#include "ColliderTag.h"
#include "Camera.h"
#include "Controller.h"
#include "GameVariables.h"
#include "Constant.h"
#include "SpriteManager.h"
#include "Jauge.h"
#include "FrogTongue.h"
#include "MeshManager.h"


using namespace nam;
using namespace DirectX;

void Frog1::OnInit()
{
    Frog::OnInit();

    MeshRendererComponent& mrc = GetComponent<MeshRendererComponent>();
    mrc.mp_mesh = MeshManager::GetMesh(MeshTag::Frog1);

    TransformComponent& tc = GetComponent<TransformComponent>();
    tc.SetWorldPosition({ -1.f,2.f,0.f });

    AddComponent<Frog1Tag>({});

    BoxColliderComponent& box = SetBoxCollider();
    box.m_tag = (size)ColliderTag::FrogJoel;
    box.m_shouldCollideWith.insert((size)ColliderTag::Platform);
    box.m_shouldCollideWith.insert((size)ColliderTag::Ground);
    box.m_shouldCollideWith.insert((size)ColliderTag::FrogEllie);
    box.m_shouldCollideWith.insert((size)ColliderTag::Checkpoint);
    box.m_shouldCollideWith.insert((size)ColliderTag::TongueEllie);

    Scene& scene = GetScene();
    m_jauge = &scene.CreateGameObject<Jauge>();
    m_jaugeTimer.Init(m_jaugeTimerTarget, true);

    m_tongue = &scene.CreateGameObject<FrogTongue>(false);
    TransformComponent& tongueTransform = m_tongue->GetComponent<TransformComponent>();
    tongueTransform.SetParent(&GetComponent<TransformComponent>());
    BoxColliderComponent& tongueCollider = m_tongue->GetComponent<BoxColliderComponent>();
    tongueCollider.m_tag = (size)ColliderTag::TongueJoel;
    tongueCollider.m_shouldCollideWith.insert((size)ColliderTag::FrogEllie);
    m_tongue->SetFrog(this);

    SetBehavior();
    SetController();

    m_jaugeProgress = m_jaugeTimerTarget; 
    m_isFrogActive = true;
}

void Frog1::UpdateJaugeDisplay(float progress)
{
    float baseInterval = m_jaugeTimerTarget * 0.2f;
    float interval1 = baseInterval;         
    float interval2 = baseInterval * 2.f;  
    float interval3 = baseInterval * 3.f;   
    float interval4 = baseInterval * 4.f;   

    if (progress <= 0.f)
        m_jauge->SetJauge(JaugeType::Jauge0);
    else if (progress < interval1)
        m_jauge->SetJauge(JaugeType::Jauge1);
    else if (progress < interval2)
        m_jauge->SetJauge(JaugeType::Jauge2);
    else if (progress < interval3)
        m_jauge->SetJauge(JaugeType::Jauge3);
    else if (progress < interval4)
        m_jauge->SetJauge(JaugeType::Jauge4);
    else
        m_jauge->SetJauge(JaugeType::Jauge5);
}

void Frog1::SpitOut()
{
    if (CheckComponent<Frog2Tag>() == false)
        return;

    TransformComponent& transform = GetComponent<TransformComponent>();
    Swallow& swallow = GetComponent<Swallow>();

    float offset = 3.f;
    XMFLOAT3 pos = transform.GetWorldPosition();
    XMFLOAT3 forward = transform.GetWorldForward();
    XMFLOAT3 newPos = { pos.x + (forward.x * offset), pos.y + forward.y, pos.z + (forward.z * offset) };
    m_otherFrogTransform->SetWorldPosition(newPos);
    m_otherFrogTransform->SetWorldScale({ 1.f, 1.f, 1.f });
    swallow.m_hasSwallowed = false;

    m_otherFrogCollider->m_shouldCollideWith.insert((size)ColliderTag::FrogJoel);
    m_otherFrogCollider->m_shouldCollideWith.insert((size)ColliderTag::TongueJoel);
    m_otherFrogPhysic->m_useGravity = true;

}

void Frog1::IsSwallowed()
{
    if (CheckComponent<Frog2Tag>() == false)
        return;

    TransformComponent& transform = GetComponent<TransformComponent>();
    Swallow& swallow = GetComponent<Swallow>();
    BoxColliderComponent& box = GetComponent<BoxColliderComponent>();
    PhysicComponent& pc = GetComponent<PhysicComponent>();

    box.m_shouldCollideWith.erase((size)ColliderTag::FrogEllie);
    box.m_shouldCollideWith.erase((size)ColliderTag::TongueEllie);
    transform.SetWorldScale({ 0.01f, 0.01f, 0.01f });
    transform.SetWorldPosition(m_otherFrogTransform->GetWorldPosition());
    pc.m_useGravity = false;
    swallow.m_isSwallowed = true;

}

void Frog1::OnUpdate()
{
    float dt = App::Get()->GetChrono().GetScaledDeltaTime();
    PhysicComponent& pc = GetComponent<PhysicComponent>();

    Frog::OnUpdate();

    if (m_isOrientedWall && m_isFrogActive)
    {
        m_isRecharging = false;
        m_jauge->SetActive(true);

        m_jaugeProgress -= dt;

        UpdateJaugeDisplay(m_jaugeProgress);

        if (m_jaugeProgress <= 0.f)
        {
            m_jaugeProgress = 0.f;

            m_jauge->SetJauge(JaugeType::Jauge0);
            pc.m_dirGravity = m_gravity;
            m_isOrientedWall = false;
        }
    }
    else if (m_isorientedGround && m_jaugeProgress < m_jaugeTimerTarget && m_isFrogActive)
    {
        m_isRecharging = true;
        m_jauge->SetActive(true);

        m_jaugeProgress += dt * (m_jaugeTimerTarget / m_rechargeRate);

        UpdateJaugeDisplay(m_jaugeProgress);

        if (m_jaugeProgress >= m_jaugeTimerTarget)
        {
            m_jaugeProgress = m_jaugeTimerTarget;
            m_isRecharging = false;
            m_jauge->SetJauge(JaugeType::Jauge5);
            m_jauge->SetActive(false);
        }
    }
    else if (!m_isOrientedWall && !m_isRecharging)
        m_jauge->SetActive(false);
    
    else if (!m_isFrogActive)
        m_jauge->SetActive(false);

}

void Frog1::OnController()
{
    if (GameVariables::s_isGamePaused)
        return;

    if (Controller::Get(ControlType::SwitchFrog1))
        m_isFrogActive = true;

    if (Controller::Get(ControlType::SwitchFrog2))
        m_isFrogActive = false;

    if (!m_isFrogActive)
        return;

    if (m_isSpacePressed)
    {
        PhysicComponent& physic = GetComponent<PhysicComponent>();
        physic.m_dirGravity = m_gravity;
        m_isOnWall = false;
    }

    Frog::OnController();

    if (m_isOnWall)
        ControllerMoveWall();


    Swallow& swallow = GetComponent<Swallow>();
    if (Input::IsKeyDown('F') && swallow.m_hasSwallowed && (m_isGrounded || m_isOnWall))
    {
        SpitOut();
    }
}

void Frog1::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
    Frog::OnCollision(self, other);
    PhysicComponent& physic = GetComponent<PhysicComponent>();

    bool onFrog = (other.m_tag == (size)ColliderTag::FrogEllie) && self.m_normal.y < 0.f;
    m_isOnWall = self.m_normal.y == 0.f && (other.m_tag != (size)ColliderTag::FrogEllie);
    

    if (onFrog)
    {
        m_isGrounded = true;
        m_isorientedGround = true;
        m_isOnWall = false;
        physic.m_useGravity = false;
        physic.m_velocity = { 0.f,0.f,0.f };
    }
    else if (m_isOnWall)
    {
        CollisionOnWall(self, other);
    }
    
    if (other.m_tag == (size)ColliderTag::TongueEllie)
    {
        IsSwallowed();
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
        if (Controller::Get(ControlType::Up))
            forward += 1.f;

        if (Controller::Get(ControlType::Down))
            forward -= 1.f;

        if (Controller::Get(ControlType::Left))
            right -= 1.f;

        if (Controller::Get(ControlType::Right))
            right += 1.f;
    }

    if (forward == 0.f && right == 0.f)
        return;

    MoveWall(forward, right);
}

void Frog1::CollisionOnWall(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
    if (m_jaugeProgress <= 0.f)
        return;

    PhysicComponent& physic = GetComponent<PhysicComponent>();
    TransformComponent& transform = GetComponent<TransformComponent>();

    m_gravityTimer.ResetProgress();
    m_isOrientedWall = true;
    m_isGrounded = false;
    m_isorientedGround = false;
    m_isRecharging = false;
    m_normal = other.m_normal;
    physic.m_dirGravity = self.m_normal;
    physic.m_velocity = { 0.f,0.f,0.f };

    XMVECTOR vNormal = XMLoadFloat3(&m_normal);

    XMFLOAT3 currentFwd = transform.GetWorldForward();
    XMVECTOR vCurrentFwd = XMLoadFloat3(&currentFwd);
    XMVECTOR vProjFwd = vCurrentFwd - XMVectorScale(vNormal, XMVectorGetX(XMVector3Dot(vCurrentFwd, vNormal)));

    float projLen = XMVectorGetX(XMVector3Length(vProjFwd));

    XMVECTOR vForward = { 0.f, 0.f, 0.f };
    if (projLen > EPSILON)
    {
        vForward = XMVector3Normalize(vProjFwd);
    }
    else
    {
        XMVECTOR vGlobalUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);
        XMVECTOR vRight = XMVector3Normalize(XMVector3Cross(vGlobalUp, vNormal));

        vForward = XMVector3Normalize(XMVector3Cross(vNormal, vRight));
    }

    XMFLOAT3 newForward;
    XMStoreFloat3(&newForward, vForward);
    transform.LookToWorld(newForward, m_normal);
}
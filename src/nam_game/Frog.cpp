#include "pch.h"
#include "Frog.h"
#include "Camera.h"
#include "Constant.h"
#include "ColliderTag.h"
#include "FrogArrow.h"
#include "FrogTongue.h"
#include "Controller.h"

using namespace nam;
using namespace DirectX;

void Frog::OnInit()
{
    MeshRendererComponent mrc;
    mrc.CreateMeshInstance();
    mrc.mp_mesh->BuildBox({ 1.f,1.f, 1.f }, { 0.5f,0.5f,0.5f,1.f });
    AddComponent<MeshRendererComponent>(mrc);

    TransformComponent tc;
    tc.SetWorldPosition({ -1.f,2.f,0.f });
    AddComponent<TransformComponent>(tc);

    AddComponent<PhysicComponent>(PhysicComponent());

    Scene& scene = GetScene();
    m_arrow = &scene.CreateGameObject<FrogArrow>(false);
    TransformComponent& arrowTransform = m_arrow->GetComponent<TransformComponent>();
    arrowTransform.SetParent(&GetComponent<TransformComponent>());  
    m_arrowTimer.Init(m_targetTimeArrow);

    m_stompedTimer.Init(m_targetTimeStomped);
    m_unstompTimer.Init(m_unstompStepDuration);

    m_tongue = &scene.CreateGameObject<FrogTongue>(false);
    TransformComponent& tongueTransform = m_tongue->GetComponent<TransformComponent>();
    tongueTransform.SetParent(&GetComponent<TransformComponent>());

    m_gravityTimerTarget = 0.5f;
    m_gravityTimer.Init(m_gravityTimerTarget);

    m_collectTimerTarget = 2.0f;
    m_collectTimer.Init(m_collectTimerTarget, true, true);
}

void Frog::OnUpdate()
{
    float dt = App::Get()->GetChrono().GetScaledDeltaTime();
    m_arrowTimer.Update(dt);
    m_stompedTimer.Update(dt);
    m_unstompTimer.Update(dt);
    m_gravityTimer.Update(dt);
    m_collectTimer.Update(dt);

    if (m_arrowTimer.IsTargetReached())
    {
        m_arrow->SetActive(false);
        m_arrowTimer.ResetProgress();
    }

    if (m_isStompted && m_stompedTimer.IsTargetReached())
    {
        m_unstompScales.push_back({ m_baseScale });
        float xDiff = m_stompedScale.x - m_baseScale.x;
        float yDiff = m_stompedScale.y - m_baseScale.y;
        float zDiff = m_stompedScale.z - m_baseScale.z;
        float invUnstompSteps = 1.f / m_unstompSteps;
        for (size i = 0; i < m_unstompSteps; i++)
        {
            float t = i * invUnstompSteps;
            m_unstompScales.push_back({ m_baseScale.x + t * xDiff, m_baseScale.y + t * yDiff, m_baseScale.z + t * zDiff });
        }
        m_unstompTimer.ResetProgress();
        TransformComponent& t = GetComponent<TransformComponent>();
        m_jumpImpulse = 5.f;
        Jump(t.GetWorldUp());
        m_isStompted = false;
    }

    if (!m_unstompScales.empty() && m_unstompTimer.IsTargetReached())
    {
        m_unstompTimer.ResetProgress();
        TransformComponent& t = GetComponent<TransformComponent>();
        t.SetWorldScale(m_unstompScales.back());
        m_unstompScales.pop_back();
    }


    if (m_isFiring && m_tongue->IsArrived())
    {
        m_isFiring = false;
    }

    
    if (m_gravityTimer.IsTargetReached())
    {
        PhysicComponent& physic = GetComponent<PhysicComponent>();
        m_isOnWall = false;
        m_isOrientedWall = false;
        physic.m_useGravity = true;
        physic.m_dirGravity = m_gravity;
        m_gravityTimer.ResetProgress();
    }

    if (!m_isFrogActive)
        return;

    if (m_isSpacePressed && (m_isGrounded || m_isOnWall))
        ChargeJump();

    RotateUpdate();
    Rotate();  
}

void Frog::OnController()
{
    if (!m_isFrogActive)
        return;

    ControllerJump();
    ControllerMove();
    ControllerFlying();
    ControllerTongue();
    ControllerGroundPound();
    InclineArrow();
    
    if (Input::IsKeyDown('K'))
        Respawn();
}


void Frog::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
    //if (onPlateform || onFloor)
    //    FloorWallCollision(self,other);

    if (other.m_tag == (size)ColliderTag::FrogEllie || other.m_tag == (size)ColliderTag::FrogJoel)
        FrogCollision(self,other);

    PhysicComponent& physic = GetComponent<PhysicComponent>();
    TransformComponent& transform = GetComponent<TransformComponent>();

    //XMFLOAT3 selfNormal = self.m_normal;
    //XMVECTOR vSelfNormal = XMLoadFloat3(&selfNormal);
    //XMFLOAT3 frogUp = transform.GetWorldUp();
    //XMVECTOR vFrogUp = XMLoadFloat3(&frogUp);
    //float dotUp = XMVectorGetX(XMVector3Dot(vSelfNormal, vFrogUp));

    bool onPlateform = (other.m_tag == (size)ColliderTag::Platform || other.m_tag == (size)ColliderTag::PressurePlate) &&  self.m_normal.y <= -0.5f;
    bool onFloor = other.m_tag == (size)ColliderTag::Ground;

    if (onPlateform || onFloor)
    {
        m_gravityTimer.ResetProgress();

        UseGravity(other.m_normal);
       
        m_isGrounded = true;
        m_isorientedGround = true;
        m_isOnWall = false;
        m_isOrientedWall = false;
        physic.m_dirGravity = self.m_normal;
        physic.m_velocity = { 0.f,0.f,0.f };
        m_normal = other.m_normal;

        if (m_normal.y == 1)
        {
            transform.SetWorldUp(m_normal);
        }
        else
        {
            XMVECTOR vNormal = XMLoadFloat3(&m_normal);

            XMFLOAT3 currentFwd = transform.GetWorldForward();
            XMVECTOR vCurrentFwd = XMLoadFloat3(&currentFwd);
            XMVECTOR vProjFwd = vCurrentFwd - XMVectorScale(vNormal, XMVectorGetX(XMVector3Dot(vCurrentFwd, vNormal)));

            float projLen = XMVectorGetX(XMVector3Length(vProjFwd));

            XMVECTOR vForward;
            if (projLen > EPSILON)
            {
                vForward = XMVector3Normalize(vProjFwd);
            }
            else
            {
                float dotY = abs(XMVectorGetX(XMVector3Dot(vNormal, XMVectorSet(0.f, 1.f, 0.f, 0.f))));
                XMVECTOR vRef = (dotY < 0.9f)
                    ? XMVectorSet(0.f, 1.f, 0.f, 0.f)
                    : XMVectorSet(0.f, 0.f, 1.f, 0.f);
                XMVECTOR vRight = XMVector3Normalize(XMVector3Cross(vRef, vNormal));
                vForward = XMVector3Normalize(XMVector3Cross(vNormal, vRight));
            }

            XMFLOAT3 newForward;
            XMStoreFloat3(&newForward, vForward);
            transform.LookToWorld(newForward, m_normal);
        }
    }

    if (other.m_tag == (size)ColliderTag::Checkpoint)
    {
        TransformComponent* transform = other.m_transform;
        XMFLOAT3 m_center = transform->GetWorldPosition();
        SetCheckpoint(m_center);
    }

    if (other.m_tag == (size)ColliderTag::CollectDrag)
    {
        std::cout << "storm" << std::endl;
        m_isFlying = true;
    }
}

void Frog::ChargeJump()
{
    float dt = App::Get()->GetChrono().GetScaledDeltaTime();
    m_jumpImpulse += m_maxImpulse * dt * m_chargeJumpRate;
    m_jumpImpulse = std::clamp(m_jumpImpulse, 0.f, m_maxImpulse);
    if (m_jumpImpulse == m_maxImpulse)
    {
        TransformComponent& arrowTransform = m_arrow->GetComponent<TransformComponent>();
        XMFLOAT3 impulse = arrowTransform.GetWorldForward();
        Jump(impulse);
        m_arrow->SetActive(false);
        m_arrowTimer.ResetProgress();
    }
}

void Frog::Jump(XMFLOAT3 direction)
{   
    XMVECTOR vimpulse = XMLoadFloat3(&direction);
    vimpulse = XMVectorScale(vimpulse, m_jumpImpulse);

    XMFLOAT3 impulse;
    XMStoreFloat3(&impulse, vimpulse);
    m_jumpImpulse = 0.f;

    PhysicComponent& physic = GetComponent<PhysicComponent>();
    physic.AddImpulse(impulse);

    physic.m_useGravity = true;
    m_isorientedGround = true;
    m_isGrounded = false;
    m_isOnWall = false;
}

void Frog::Rotate()
{

    Ecs& ecs = GetEcs();

    XMFLOAT3 impulse = { 0.f, 0.0f, 0.f };

    TransformComponent* transform = &GetComponent<TransformComponent>();
    TransformComponent* cameraTransform = nullptr;
    ecs.ForEach<CameraTag, TransformComponent>([&](uint32_t entity, CameraTag& tag, TransformComponent& transform)
        {
            cameraTransform = &transform;
        });

    if (cameraTransform == nullptr || transform == nullptr)
        return;
    
    XMVECTOR vUp = XMLoadFloat3(&m_normal);

    XMFLOAT3 camForward = cameraTransform->GetWorldForward();
    XMVECTOR vcamForward = XMLoadFloat3(&camForward);
    XMVECTOR vCamFwdProj = vcamForward - XMVectorScale(vUp, XMVectorGetX(XMVector3Dot(vcamForward, vUp)));

    float projLen = XMVectorGetX(XMVector3Length(vCamFwdProj));
    if (projLen < EPSILON)
        return;

    vCamFwdProj = XMVector3Normalize(vCamFwdProj);

    XMFLOAT3 frogForward = transform->GetWorldForward();
    XMVECTOR vfrogForward = XMLoadFloat3(&frogForward);
    vfrogForward = XMVector3Normalize(vfrogForward);

    XMVECTOR vectDiffAngles = XMVectorSubtractAngles(vCamFwdProj, vfrogForward);
    XMFLOAT3 diffAngles;
    XMStoreFloat3(&diffAngles, vectDiffAngles);

    if (diffAngles.x >= PI_DIV12 || diffAngles.x <= -PI_DIV12 || diffAngles.z >= PI_DIV12 || diffAngles.z <= -PI_DIV12)
    {
        if (m_isGrounded || m_isOnWall)
        {
            XMFLOAT3 impulse;
            XMStoreFloat3(&impulse, XMVectorScale(vUp, 2.f));

            PhysicComponent& physic = GetComponent<PhysicComponent>();
            physic.AddImpulse(impulse);
            physic.m_useGravity = true;
            m_isGrounded = false;
            m_isorientedGround = true;
            m_isOnWall = false;

        }
    }
}

void Frog::RotateUpdate()
{
    if (m_isGrounded)
        return;

    Ecs* ecs = &App::Get()->GetEcs();

    TransformComponent* transform = &GetComponent<TransformComponent>();
    TransformComponent* cameraTransform = nullptr;
    ecs->ForEach<CameraTag, TransformComponent>([&](uint32_t entity, CameraTag& tag, TransformComponent& transform)
        {
            cameraTransform = &transform;
        });

    if (cameraTransform == nullptr || transform == nullptr)
    {
        return;
    }
     

    XMVECTOR vUp = XMLoadFloat3(&m_normal);

    XMFLOAT3 camForward = cameraTransform->GetWorldForward();
    XMVECTOR vcamForward = XMLoadFloat3(&camForward);
    XMVECTOR vTargetFwd = XMVector3Normalize(vcamForward - XMVectorScale(vUp, XMVectorGetX(XMVector3Dot(vcamForward, vUp))));

    XMFLOAT3 frogForward = transform->GetWorldForward();
    XMVECTOR vfrogForward = XMLoadFloat3(&frogForward);
    vfrogForward = XMVector3Normalize(vfrogForward);

    XMVECTOR vDot = XMVector3Dot(vfrogForward, vTargetFwd);

    float dot = XMVectorGetX(vDot);

    if (dot >= 1.f - EPSILON)
        return;

    XMVECTOR vNewFwd = XMVector3Normalize(XMVectorLerp(vfrogForward, vTargetFwd, 0.15f));

    XMFLOAT3 newFwd;
    XMStoreFloat3(&newFwd, vNewFwd);

    XMFLOAT3 upToUse;
    XMStoreFloat3(&upToUse, vUp);
    transform->LookToWorld(newFwd, upToUse);
}

void Frog::InclineArrow()
{
    float dt = App::Get()->GetChrono().GetScaledDeltaTime();

    if (Controller::Get(ControlType::MoveArrowDown))
    {
        m_slope += dt * 0.5f;
        m_arrow->SetActive(true);
    }

    if (Controller::Get(ControlType::MoveArrowUp))
    {
        m_slope -= dt * 0.5f;
        m_arrow->SetActive(true);
    }

    m_slope = std::clamp(m_slope, -XM_PIDIV2, 0.f);
    m_arrow->SetSlope(m_slope);
}

void Frog::ControllerMove()
{
    float forward = 0.f;
    float right = 0.f;

    if (m_isGrounded)
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

    Move(forward, right);
}

void Frog::ControllerJump()
{
    if (Controller::Get(ControlType::JumpCharge))
        m_isSpacePressed = true;

    if (Controller::Get(ControlType::JumpRelease))
    {
        m_isSpacePressed = false;

        if (m_isGrounded || m_isOnWall)
        {
            TransformComponent& arrowTransform = m_arrow->GetComponent<TransformComponent>();
            XMFLOAT3 impulse = arrowTransform.GetWorldForward();
            Jump(impulse);
            m_arrow->SetActive(false);
            m_arrowTimer.ResetProgress();
        }
    }
}

void Frog::ControllerTongue()
{
    if (Controller::Get(ControlType::FireTongue))
    {
        if (m_isFiring)
        {
            m_isFiring = false;
        }
        else
        {
            m_isFiring = true;
        }

        m_tongue->SetFire(m_isFiring, *this);
    }
}

void Frog::ControllerGroundPound()
{
    if (m_isGrounded)
        return;
    
    if (!Controller::Get(ControlType::GroundPound))
        return;

    PhysicComponent& pc = GetComponent<PhysicComponent>();

    pc.m_velocity = {0,0,0};

    if (m_isOnWall)
    {
        TransformComponent& t = GetComponent<TransformComponent>();
        pc.AddImpulse(t.GetWorldUp());
    }
    pc.AddImpulse({ 0,-20,0 });
}

void Frog::ControllerFlying()
{
    if (m_collectTimer.IsTargetReached())
        return;

    float forward = 0.f;
    float right = 0.f;

    if (m_isFlying)
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

    Move(forward, right);
}


void Frog::UseGravity(XMFLOAT3 normal)
{
    PhysicComponent& physic = GetComponent<PhysicComponent>();
    TransformComponent& transform = GetComponent<TransformComponent>();

    XMFLOAT3 up = transform.GetWorldUp();

    XMVECTOR vUp = XMLoadFloat3(&up);
    XMVECTOR vOtherNormal = XMLoadFloat3(&normal);

    XMVECTOR vSub = vUp - vOtherNormal;
    XMFLOAT3 sub;
    XMStoreFloat3(&sub, vSub);

    if (abs(sub.x) <= EPSILON && abs(sub.y) <= EPSILON && abs(sub.z) <= EPSILON)
        physic.m_useGravity = false;
    else
        physic.m_useGravity = true;
}

void Frog::FloorWallCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
    TransformComponent& transform = GetComponent<TransformComponent>();
    PhysicComponent& physic = GetComponent<PhysicComponent>();

    m_isGrounded = true;
    m_isOnWall = false;
    m_isOrientedWall = false;
    physic.m_dirGravity = self.m_normal;
    physic.m_velocity = { 0.f,0.f,0.f };
    m_normal = other.m_normal;

    if (m_normal.y == 1)
    {
        transform.SetWorldUp(m_normal);
    }
    else
    {
        XMVECTOR vNormal = XMLoadFloat3(&m_normal);

        XMVECTOR vGlobalUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);
        XMVECTOR vRight = XMVector3Normalize(XMVector3Cross(vGlobalUp, vNormal));

        XMVECTOR vForward = XMVector3Normalize(XMVector3Cross(vNormal, vRight));

        XMFLOAT3 newForward;
        XMStoreFloat3(&newForward, vForward);

        transform.LookToWorld(newForward, m_normal);

    }
}

void Frog::FrogCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
    XMFLOAT3 up = self.m_transform->GetWorldUp();
    XMVECTOR vUp = XMLoadFloat3(&up);
    XMVECTOR collisionNormal = XMLoadFloat3(&self.m_normal);
    float dot = XMVectorGetX(XMVector3Dot(vUp, collisionNormal));
    float angle = acosf(dot); 
    float threshold = XMConvertToRadians(45.0f);

    if (angle <= threshold) {
        m_isStompted = true;
        self.m_transform->SetWorldScale(m_stompedScale);
        m_stompedTimer.ResetProgress();
        m_unstompScales.clear();
        m_isGrounded = false;
        PhysicComponent& physic = GetComponent<PhysicComponent>();
        physic.m_useGravity = true;
    }
}

void Frog::Move(float _forward, float _right)
{
    m_jumpImpulse = 2.f;

    XMVECTOR vDirection = XMLoadFloat3(&m_normal);

    TransformComponent& transform = GetComponent<TransformComponent>();
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
    Jump(direction);
}

void Frog::SetCheckpoint(XMFLOAT3 center)
{
    m_checkpointCenter = center;
    m_checkpointCenter.y += 2.f;
    m_hasCheckpoint = true;
}

void Frog::Respawn()
{
    if (!m_hasCheckpoint)
        return;

    TransformComponent& transform = GetComponent<TransformComponent>();
    transform.SetWorldPosition(m_checkpointCenter);

    PhysicComponent& physic = GetComponent<PhysicComponent>();
    physic.m_velocity = { 0.f, 0.f, 0.f };
    physic.m_useGravity = true;
    physic.m_dirGravity = m_gravity;

    m_isGrounded = false;
    m_isorientedGround = true;
    m_isOnWall = false;
    m_normal = { 0.f, 1.f, 0.f };
}

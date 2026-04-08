#include "pch.h"
#include "PressurePlate.h"
#include "EventRegister.h"
#include "ColliderTag.h"

using namespace nam;
using namespace DirectX;

void PressurePlate::OnInit()
{
	m_eventId = EventRegister::GenerateId();

	AddComponent<TransformComponent>({});

	BoxColliderComponent& box = SetBoxCollider();
	box.m_tag = (size)ColliderTag::PressurePlate;
	box.m_shouldCollideWith.insert((size)ColliderTag::FrogEllie);
	box.m_shouldCollideWith.insert((size)ColliderTag::FrogJoel);
	box.m_shouldCollideWith.insert((size)ColliderTag::Tongue);

	MeshRendererComponent mrc;
	mrc.CreateMeshInstance();
	mrc.mp_mesh->BuildBox({ 1,0.3f,1 }, {1,1,1,1});
	AddComponent<MeshRendererComponent>(mrc);

	m_timerCanToggleDelay.Init(m_timerCanToggleDelayTarget);
	m_timerUpDelay.Init(m_timerUpDelayTarget);

	SetBehavior();
}

void PressurePlate::OnUpdate()
{
	EventRegister::SetEvent(m_eventId, m_isPressed);
	float dt = App::Get()->GetChrono().GetScaledDeltaTime();

	if (m_toggleMode && !m_canToggle)
	{
		m_timerCanToggleDelay.Update(dt);
		if (m_timerCanToggleDelay.IsTargetReached())
			m_canToggle = true;
	}
	else if (!m_toggleMode && m_isPressed)
	{
		m_timerUpDelay.Update(dt);
		if (m_timerUpDelay.IsTargetReached())
		{
			m_isPressed = false;
			TransformComponent& t = GetComponent<TransformComponent>();
			t.SetWorldScale({ 1,1,1 });
		}
	}
}

void PressurePlate::OnCollision(const SingleCollisionInfo& self, const SingleCollisionInfo& other)
{
	bool hasPressedChange = false;
	if (m_toggleMode)
	{
		if (m_canToggle)
		{
			m_canToggle = false;
			m_isPressed = !m_isPressed;
			hasPressedChange = true;
		}
		m_timerCanToggleDelay.ResetProgress();
	}
	else
	{
		hasPressedChange = !m_isPressed;
		m_isPressed = true;
		m_timerUpDelay.ResetProgress();
	}

	if (hasPressedChange && m_isPressed)
		self.m_transform->SetWorldScale(m_pushedScale);
	else if (hasPressedChange)
		self.m_transform->SetWorldScale({ 1,1,1 });
}

uint32_t PressurePlate::GetEventId()
{
	return m_eventId;
}

void PressurePlate::SetToggleMode(bool toggleMode)
{
	m_toggleMode = toggleMode;
}

void PressurePlate::SetPosition(DirectX::XMFLOAT3 position)
{
	TransformComponent& t = GetComponent<TransformComponent>();
	t.SetWorldPosition(position);
}
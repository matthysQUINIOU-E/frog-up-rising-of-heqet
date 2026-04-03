#include "pch.h"
#include "Frog.h"
#include "FrogTongue.h"
#include "ColliderTag.h"

using namespace nam;
using namespace DirectX;

void FrogTongue::OnInit()
{
	MeshRendererComponent tongueMesh;
	tongueMesh.CreateMeshInstance();
	tongueMesh.mp_mesh->BuildBox({ 0.1f, 0.1f, 0.99f }, { 1.0f, 0.411f, 0.705f, 1.0f });
	AddComponent<MeshRendererComponent>(tongueMesh);

	TransformComponent tongueTransform;
	AddComponent<TransformComponent>(tongueTransform);

	BoxColliderComponent& tongueCollider = SetBoxCollider();
	tongueCollider.m_tag = (size)ColliderTag::Tongue;
	tongueCollider.m_shouldCollideWith.insert((size)ColliderTag::Platform);
	tongueCollider.m_noIntersectionPush = true;

	SetBehavior();
}

void FrogTongue::OnUpdate()
{
	float dt = App::Get()->GetChrono().GetScaledDeltaTime();

	if (!m_isFiring)
		return;

	m_pos = m_frog.GetComponent<TransformComponent>().GetWorldPosition(); // bancal la ligne mais ça marche donc tranquille

	TransformComponent& tc = GetComponent<TransformComponent>();
	XMFLOAT3 fwd = tc.GetWorldForward();

	if (!m_arrived)
	{
		m_move += m_speed * dt;
		if (m_move >= m_maxDistance)
		{
			m_move = m_maxDistance;
			m_arrived = true;
		}
	}
	else
	{
		m_move -= m_speed * dt;
		if (m_move <= 0.0f)
		{
			m_move = 0.0f;
			m_arrived = false;
			m_isFiring = false;
		}
	}

	float scaleZ;

	if (m_move > 0.01f)
	{
		scaleZ = m_move;
	}
	else
	{
		scaleZ = 0.01f;
	}
	tc.SetWorldScale({ 1.0f, 1.0f, scaleZ });

	float offset = m_move / 2.0f;

	XMFLOAT3 newPos = { m_pos.x + (fwd.x * offset), m_pos.y + (fwd.y * offset), m_pos.z + (fwd.z * offset) };

	tc.SetWorldPosition(newPos);
}

void FrogTongue::OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other)
{
	if(other.m_tag == (size)ColliderTag::Platform)
		m_arrived = true;
}

void FrogTongue::SetFire(bool _fire, Frog _frog)
{
	if (_fire && !m_isFiring)
	{
		m_isFiring = true;
		m_arrived = false;
		m_move = 0.0f;

		m_frog = _frog;
		m_pos = m_frog.GetComponent<TransformComponent>().GetWorldPosition();
	}
	else if (!_fire && m_isFiring)
	{
		m_arrived = true;
	}
}

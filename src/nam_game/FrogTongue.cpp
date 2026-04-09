#include "pch.h"
#include "FrogTongue.h"
#include "ColliderTag.h"
#include "Swallow.h"

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
	tongueCollider.m_shouldCollideWith.insert((size)ColliderTag::Platform);
	tongueCollider.m_shouldCollideWith.insert((size)ColliderTag::Ground);
	tongueCollider.m_shouldCollideWith.insert((size)ColliderTag::PressurePlate);
	tongueCollider.m_noIntersectionPush = true;

	SetBehavior();
}

void FrogTongue::OnUpdate()
{
	float dt = App::Get()->GetChrono().GetScaledDeltaTime();

	if (!m_isFiring)
		return;

	m_pos = m_frog->GetComponent<TransformComponent>().GetWorldPosition(); 

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
	m_arrived = true;
	bool frog1 = self.m_tag == (size)ColliderTag::TongueJoel && other.m_tag == (size)ColliderTag::FrogEllie;
	bool frog2 = self.m_tag == (size)ColliderTag::TongueEllie && other.m_tag == (size)ColliderTag::FrogJoel;

	if(frog1 || frog2)
	{
		Swallow& sw = m_frog->GetComponent<Swallow>();
		sw.m_hasSwallowed = true;
	}
}

void FrogTongue::SetFrog(Frog* frog)
{
	m_frog = frog;
}

void FrogTongue::SetFire(bool _fire)
{
	if (_fire && !m_isFiring)
	{
		m_isFiring = true;
		m_arrived = false;
		m_move = 0.0f;
	}
	else if (!_fire && m_isFiring)
	{
		m_arrived = true;
	}
}

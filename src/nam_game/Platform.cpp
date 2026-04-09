#include "pch.h"
#include "Platform.h"
#include "ColliderTag.h"
#include "MeshManager.h"
#include "EventRegister.h"

using namespace nam;
using namespace DirectX;

void Platform::OnInit()
{
	BoxColliderComponent& box = SetBoxCollider();
	box.m_tag = (size)ColliderTag::Platform;
	box.m_shouldCollideWith.insert((size)ColliderTag::FrogEllie);
	box.m_shouldCollideWith.insert((size)ColliderTag::FrogJoel);
	box.m_shouldCollideWith.insert((size)ColliderTag::TongueEllie);
	box.m_shouldCollideWith.insert((size)ColliderTag::TongueJoel);
	// add checkpoint / others...

	AddComponent<TransformComponent>({});
	MeshRendererComponent mrc;
	mrc.mp_mesh = MeshManager::GetMesh(MeshTag::Platform1); // TODO :: change
	AddComponent<MeshRendererComponent>(mrc);

	SetBehavior();
	SetBoxCollider();
}

void Platform::OnUpdate()
{
	if (m_waypoints.size() <= 1)
		return;

	if (m_listenToEvent)
		m_move = EventRegister::GetEvent(m_eventListen);

	if (m_move)
	{
		bool reached = MoveToward(m_waypoints[m_waypointIndex]);
		if (reached)
		{
			if (m_waypointIndex == m_waypoints.size() - 1 && m_loopWaypoints)
			{
				m_waypointIndex = 0;
				std::reverse(m_waypoints.begin(), m_waypoints.end());
			}
			else
			{
				m_waypointIndex++;
			}
		}

		float dt = App::Get()->GetChrono().GetScaledDeltaTime();
		std::vector<TransformComponent*> componentToUnlink;
		for (auto& it : m_linkedTransforms)
		{
			it.second += dt;
			if (it.second >= m_linkDuration)
				componentToUnlink.push_back(it.first);
		}

		for (size_t i = 0; i < componentToUnlink.size(); i++)
		{
			m_linkedTransforms.erase(componentToUnlink[i]);
		}
	}
}

void Platform::OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other)
{
	if (other.m_tag == (size)ColliderTag::TongueEllie || other.m_tag == (size)ColliderTag::TongueJoel)
		return;

	m_linkedTransforms[other.m_transform] = 0.f;
}

void Platform::SetEventListen(uint32_t id)
{
	m_listenToEvent = true;
	m_move = false;
	m_eventListen = id;
}

void Platform::SetPosition(DirectX::XMFLOAT3 position)
{
	TransformComponent& transform = GetComponent<TransformComponent>();
	transform.SetWorldPosition(position);
}

void Platform::LoopWaypoints(bool loop)
{
	m_loopWaypoints = loop;
}

void Platform::SetWaypoints(std::vector<DirectX::XMFLOAT3> waypoints)
{
	m_waypoints = waypoints;
	m_waypointIndex = 0;
}

void Platform::SetSpeed(float speed)
{
	m_speed = speed;
}

void Platform::SetMesh(MeshTag meshTag)
{
	MeshRendererComponent& mrc = GetComponent<MeshRendererComponent>();
	mrc.mp_mesh = MeshManager::GetMesh(meshTag);
}

void Platform::SetTexture(TextureTag textureTag)
{
	MeshRendererComponent& mrc = GetComponent<MeshRendererComponent>();
	mrc.mp_mesh->SetTexture((size)textureTag);
}

bool Platform::MoveToward(DirectX::XMFLOAT3 pos)
{
	float dt = App::Get()->GetChrono().GetScaledDeltaTime();

	TransformComponent& transform = GetComponent<TransformComponent>();
	XMFLOAT3 currentPos = transform.GetWorldPosition();

	XMVECTOR vTarget = XMLoadFloat3(&pos);
	XMVECTOR vCurrent = XMLoadFloat3(&currentPos);

	XMVECTOR vDistance = XMVectorSubtract(vTarget, vCurrent);
	XMVECTOR vDir = XMVector3Normalize(vDistance);
	XMVECTOR vTranslation = XMVectorScale(vDir, m_speed * dt);

	float normTrans = XMVectorGetX(XMVector3Length(vTranslation));
	float normDist = XMVectorGetX(XMVector3Length(vDistance));

	XMFLOAT3 translation;
	if (normDist > normTrans)
		XMStoreFloat3(&translation, vTranslation);
	else 
		XMStoreFloat3(&translation, vDistance);

	transform.TranslateWorld(translation);
	for (auto& it : m_linkedTransforms)
	{
		it.first->TranslateWorld(translation);
	}

	return normDist <= normTrans;
}

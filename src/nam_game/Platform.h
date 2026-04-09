#pragma once
#include "MeshTag.h"

class Platform : public nam::GameObject
{
private:
	bool m_listenToEvent = false;
	uint32_t m_eventListen = 0;
	bool m_move = true;

	std::unordered_map<nam::TransformComponent*, float> m_linkedTransforms;
	float m_linkDuration = 0.5f;
	bool m_loopWaypoints = true;
	std::vector<DirectX::XMFLOAT3> m_waypoints;
	size_t m_waypointIndex = 0;
	float m_speed = 5.f;

public:
	void OnInit() override;
	void OnUpdate() override;
	void OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other) override;

	void SetPosition(DirectX::XMFLOAT3 position);

	void SetEventListen(uint32_t id);
	void LoopWaypoints(bool loop);
	void SetWaypoints(std::vector<DirectX::XMFLOAT3> waypoints);
	void SetSpeed(float speed);
	void SetMesh(MeshTag meshTag);

private:
	bool MoveToward(DirectX::XMFLOAT3 pos);
};


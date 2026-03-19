#pragma once
#include "DirectXMath.h"
#include <DirectXCollision.h>

namespace nam
{
	struct TransformComponent;
	struct MeshRendererComponent;
	struct CollisionInfo;

	struct SphereColliderComponent
	{
		u32 m_updateId = 0;
		DirectX::BoundingSphere m_box;
		std::function<void(u32 self, u32 other, const CollisionInfo& collisionInfo)> OnCollision;
		bool m_noIntersectionPush = false;

		bool m_basedOnMesh = true;
		float m_customRadius = 1.f;
		DirectX::XMFLOAT3 m_customPosOffset = { 0.f,0.f,0.f };

		size m_tag = (size)-1;
		UnSet<size> m_shouldCollideWith;

		void UpdateSphereBox(TransformComponent& transform, const MeshRendererComponent& meshRenderer, u32 updateId);
		void UpdateSphereBox(TransformComponent& meshRenderer, u32 updateId);

		bool m_dirty = true;
	};
}

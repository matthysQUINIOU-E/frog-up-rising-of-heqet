#pragma once
#include "GameObject.h"

namespace nam
{
	template<typename Component>
	void GameObject::AddComponent(const Component& data)
	{
		return App::Get()->m_ecs.AddComponent(m_entity, data);
	}

	template<typename Component>
	const bool GameObject::HasComponent()
	{
		return App::Get()->m_ecs.HasComponent<Component>(m_entity);
	}

	template<typename Component>
	Component& GameObject::GetComponent()
	{
		return App::Get()->m_ecs.GetComponent<Component>(m_entity);
	}

	template<typename T>
	inline BehaviorComponent& GameObject::SetFunctionUpdate(T* owner, void(T::* Update)())
	{
		if (HasComponent<BehaviorComponent>() == false)
		{
			BehaviorComponent behavior;
			behavior.Update = [owner, Update]() {
				(owner->*Update)();
				};
			AddComponent(behavior);
		}
		else
		{
			BehaviorComponent& behavior = GetComponent<BehaviorComponent>();
			behavior.Update = [owner, Update]() {
				(owner->*Update)();
				};
		}
		return GetComponent<BehaviorComponent>();
	}

	template<typename T>
	inline BoxColliderComponent& GameObject::SetBoxCollider(T* owner, void(T::* Collide)(u32 self, u32 other, const CollisionInfo& collisionInfo))
	{
		if (HasComponent<BoxColliderComponent>() == false)
		{
			BoxColliderComponent boxCollider;
			boxCollider.OnCollision = [owner, Collide](u32 self, u32 other, const CollisionInfo& collisionInfo) {
				(owner->*Collide)(self, other, collisionInfo);
				};

			AddComponent(boxCollider);
		}
		else
		{
			BoxColliderComponent& boxCollider = GetComponent<BoxColliderComponent>();
			boxCollider.OnCollision = [owner, Collide](u32 self, u32 other, const CollisionInfo& collisionInfo) {
				(owner->*Collide)(self, other, collisionInfo);
				};
		}
		return GetComponent<BoxColliderComponent>();
	}

	template<typename T>
	inline SphereColliderComponent& GameObject::SetSphereCollider(T* owner, void(T::* Collide)(u32 self, u32 other, const CollisionInfo& collisionInfo))
	{
		if (HasComponent<SphereColliderComponent>() == false)
		{
			SphereColliderComponent sphereCollider;
			sphereCollider.OnCollision = [owner, Collide](u32 self, u32 other, const CollisionInfo& collisionInfo) {
				(owner->*Collide)(self, other, collisionInfo);
				};

			AddComponent(sphereCollider);
		}
		else
		{
			SphereColliderComponent& sphereCollider = GetComponent<SphereColliderComponent>();
			sphereCollider.OnCollision = [owner, Collide](u32 self, u32 other, const CollisionInfo& collisionInfo) {
				(owner->*Collide)(self, other, collisionInfo);
				};
		}
		return GetComponent<SphereColliderComponent>();
	}
	template<typename T>
	inline ControllerComponent& GameObject::SetController(T* owner, void(T::* Controller)())
	{
		if (HasComponent<ControllerComponent>() == false)
		{
			ControllerComponent controller;
			controller.OnController = [owner, Controller]() {
				(owner->*Controller)();
				};
			AddComponent(controller);
		}
		else
		{
			ControllerComponent& controller = GetComponent<ControllerComponent>();
			controller.OnController = [owner, Controller]() {
				(owner->*Controller)();
				};
		}
		return GetComponent<ControllerComponent>();
	}
}
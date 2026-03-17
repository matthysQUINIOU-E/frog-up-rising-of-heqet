#include "pch.h"
#include "GameObject.h"

using namespace DirectX;

namespace nam
{
	GameObject::GameObject()
	{
		mp_scene = nullptr;
		m_entity = Entity();
		mp_ecs = &App::Get()->GetEcs();
	}

	void GameObject::Init(Scene* scene, Entity entity)
	{
		mp_scene = scene;
		m_entity = entity;
		OnInit();
	}

	void GameObject::Start()
	{
		OnStart();
	}

	void GameObject::Update()
	{
		OnUpdate();
	}

	void GameObject::Collider(u32 self, u32 other, const CollisionInfo& collisionInfo)
	{
		OnCollision(self, other, collisionInfo);
	}

	void GameObject::Controller()
	{
		OnController();
	}

	void GameObject::Destroy()
	{
		OnDestroy();
		mp_scene->DestroyGameObject(*this);
	}

	void GameObject::OnInit()
	{
	}

	void GameObject::OnStart()
	{
	}

	void GameObject::OnUpdate()
	{
	}

	void GameObject::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
	{
	}

	void GameObject::OnController()
	{
	}

	void GameObject::OnDestroy()
	{
	}

	void GameObject::SetActive(bool active)
	{
		mp_ecs->SetEntityActive(m_entity,active);
	}

	BehaviorComponent& GameObject::SetBehavior()
	{
		return SetFunctionUpdate(this, &GameObject::Update);
	}

	BoxColliderComponent& GameObject::SetBoxCollider()
	{
		return SetBoxCollider(this, &GameObject::Collider);
	}

	SphereColliderComponent& GameObject::SetSphereCollider()
	{
		return SetSphereCollider(this, &GameObject::Collider);
	}

	ControllerComponent& GameObject::SetController()
	{
		return SetController(this, &GameObject::Controller);
	}

	Entity GameObject::GetEntity()
	{
		return m_entity;
	}

	Scene* GameObject::GetScene()
	{
		return mp_scene;
	}
}
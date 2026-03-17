#pragma once
#include "App.h"
#include "Scene.h"

namespace nam
{
	template<typename System, typename... Args>
	void App::AddSystem(Args&&... args)
	{
		m_ecs.AddSystem<System>(std::forward<Args>(args)...);
	}

	template<typename System>
	void App::SetSystemEnabled(const bool enabled)
	{
		m_ecs.SetSystemEnabled(enabled);
	}

	template<typename T>
	inline T& App::CreateGameObject(size scene, bool active)
	{
		m_sceneManager.CreateOrGetScene(scene).CreateGameObject(active);
	}
}
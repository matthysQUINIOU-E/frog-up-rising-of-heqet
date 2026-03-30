#include "pch.h"
#include "SceneLevelChoice.h"
#include "ButtonExemple.h"

using namespace nam;
using namespace DirectX;

void SceneLevelChoice::Init()
{
	{
		CreateGameObject<ButtonExemple>();
	}
}

void SceneLevelChoice::Destroy()
{
}

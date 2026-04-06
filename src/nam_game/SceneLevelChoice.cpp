#include "pch.h"
#include "SceneLevelChoice.h"
#include "Button.h"
#include "BackgroudGreen.h"
#include "PlateWood.h"
#include <SceneGameplay.h>
#include <SceneTag.h>

// remove 
#include "SaveManager.h"
#include "ConfigManager.h"

using namespace nam;
using namespace DirectX;

void SceneLevelChoice::Init()
{
	CreateGameObject<BackgroudGreen>();
	CreateGameObject<PlateWood>();
	{
		Button& button = CreateGameObject<Button>();
		button.SetButtonType(ButtonType::Play);
		button.SetPosition({ 960,540 });
		button.SetOnClick(
			[]() {
				App::Get()->CreateOrGetScene<SceneGameplay>((size)SceneTag::Gameplay).SetActive(true);
				App::Get()->CreateOrGetScene<Scene>((size)SceneTag::LevelChoice).SetActive(false);
			}
		);
	}

	SaveManager::GetSave();
	ConfigManager::GetConfig();
}

void SceneLevelChoice::Destroy()
{
}

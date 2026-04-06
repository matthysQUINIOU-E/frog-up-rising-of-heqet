#include "pch.h"
#include "SceneOption.h"
#include "BackgroudGreen.h"
#include "PlateWood.h"
#include "Button.h"
#include "GameText.h"
#include "SceneTag.h"
#include "GameVariables.h"

using namespace nam;

void SceneOption::Init()
{
	CreateGameObject<BackgroudGreen>();
	CreateGameObject<PlateWood>();

	GameText& title = CreateGameObject<GameText>();
	title.SetPostion({ 875,275 });
	title.SetText("Option");
	title.SetTextSize(50);

	Button& buttonBack = CreateGameObject<Button>();
	buttonBack.SetButtonType(ButtonType::ReturnLeft);
	buttonBack.SetPosition({ 500,300 });
	buttonBack.SetOnClick(
		[]() {
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Option).SetActive(false);
			App::Get()->CreateOrGetScene<Scene>((size)GameVariables::s_lastScene).SetActive(true);
			if (GameVariables::s_lastScene == SceneTag::Pause)
			{
				App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Gameplay).SetActive(true);
			}
		}
	);
}

void SceneOption::Destroy()
{
}
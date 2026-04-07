#include "pch.h"
#include "ScenePause.h"
#include "Button.h"
#include "PlateWood.h"
#include "SceneGameplay.h"
#include "SceneTag.h"
#include "GameText.h"
#include "GameVariables.h"

using namespace nam;

void ScenePause::Init()
{
	GameText& title = CreateGameObject<GameText>();
	title.SetPostion({ 875,275 });
	title.SetText("Paused");
	title.SetTextSize(50);

	CreateGameObject<PlateWood>();
	Button& buttonOptions = CreateGameObject<Button>();
	buttonOptions.SetButtonType(ButtonType::Cog);
	buttonOptions.SetPosition({ 1420,300 });
	buttonOptions.SetOnClick(
		[]() {
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Option).SetActive(true);
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Pause).SetActive(false);
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Gameplay).SetActive(false);
			GameVariables::s_lastScene = SceneTag::Pause;
		}
	);


	Button& buttonBack = CreateGameObject<Button>();
	buttonBack.SetButtonType(ButtonType::Play);
	buttonBack.SetPosition({ 1110, 540 });
	buttonBack.SetOnClick(
		[]() {
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Pause).SetActive(false);
			GameVariables::s_isGamePaused = false;
			App::Get()->GetChrono().SetFreezeState(false);
		}
	);

	Button& buttonLevelList = CreateGameObject<Button>();
	buttonLevelList.SetButtonType(ButtonType::List);
	buttonLevelList.SetPosition({ 810, 540 });
	buttonLevelList.SetOnClick(
		[]() {
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Pause).SetActive(false);
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Gameplay).SetActive(false);
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::LevelChoice).SetActive(true);
			GameVariables::s_isGamePaused = false;
			App::Get()->GetChrono().SetFreezeState(false);
		}
	);
}

void ScenePause::Destroy()
{
}

#include "pch.h"
#include "SceneProfil.h"
#include "BackgroudGreen.h"
#include "PlateWood.h"
#include "Button.h"
#include "GameText.h"
#include "SceneTag.h"
#include "GameVariables.h"

using namespace nam;

void SceneProfil::Init()
{
	CreateGameObject<BackgroudGreen>();
	CreateGameObject<PlateWood>();

	GameText& title = CreateGameObject<GameText>();
	title.SetPostion({ 475,275 });
	title.SetText("Frog up : The rising of Heqet");
	title.SetTextSize(50);


	GameText& textP0 = CreateGameObject<GameText>();
	textP0.SetPostion({ 540,625 });
	textP0.SetText("Profile 1");

	Button& buttonP0 = CreateGameObject<Button>();
	buttonP0.SetButtonType(ButtonType::Play);
	buttonP0.SetPosition({ 660,540 });
	buttonP0.SetOnClick(
		[]() {
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Profil).SetActive(false);
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::LevelChoice).SetActive(true);
			GameVariables::s_currentProfile = 0;
		}
	);

	GameText& textP1 = CreateGameObject<GameText>();
	textP1.SetPostion({ 840,625 });
	textP1.SetText("Profile 2");

	Button& buttonP1 = CreateGameObject<Button>();
	buttonP1.SetButtonType(ButtonType::Play);
	buttonP1.SetPosition({ 960,540 });
	buttonP1.SetOnClick(
		[]() {
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Profil).SetActive(false);
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::LevelChoice).SetActive(true);
			GameVariables::s_currentProfile = 1;
		}
	);

	GameText& textP2 = CreateGameObject<GameText>();
	textP2.SetPostion({ 1140,625 });
	textP2.SetText("Profile 3");

	Button& buttonP2 = CreateGameObject<Button>();
	buttonP2.SetButtonType(ButtonType::Play);
	buttonP2.SetPosition({ 1260,540 });
	buttonP2.SetOnClick(
		[]() {
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Profil).SetActive(false);
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::LevelChoice).SetActive(true);
			GameVariables::s_currentProfile = 2;
		}
	);
}

void SceneProfil::Destroy()
{
}

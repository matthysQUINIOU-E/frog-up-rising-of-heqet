#include "pch.h"
#include "SceneLevelChoice.h"
#include "Button.h"
#include "BackgroudGreen.h"
#include "PlateWood.h"
#include "SceneGameplay.h"
#include "SceneTag.h"
#include "GameText.h"
#include "GameVariables.h"

using namespace nam;
using namespace DirectX;

void SceneLevelChoice::Init()
{
	CreateGameObject<BackgroudGreen>();
	CreateGameObject<PlateWood>();

	GameText& title = CreateGameObject<GameText>();
	title.SetPostion({ 775,275 });
	title.SetText("Level Choice");
	title.SetTextSize(50);

	// TODO change the play part when map loader ready

	GameText& textPlay1 = CreateGameObject<GameText>();
	textPlay1.SetPostion({ 525,580 });
	textPlay1.SetText("Level 1");

	Button& buttonPlay1 = CreateGameObject<Button>();
	buttonPlay1.SetButtonType(ButtonType::Play);
	buttonPlay1.SetPosition({ 610,480 });
	buttonPlay1.SetOnClick(
		[]() {
			SceneGameplay& sceneGameplay = App::Get()->CreateOrGetScene<SceneGameplay>((size)SceneTag::Gameplay);
			sceneGameplay.LoadLevel(Level::Level1);
			sceneGameplay.SetActive(true);
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::LevelChoice).SetActive(false);
		}
	);

	GameText& textPlay2 = CreateGameObject<GameText>();
	textPlay2.SetPostion({ 875,580 });
	textPlay2.SetText("Level 2");

	Button& buttonPlay2 = CreateGameObject<Button>();
	buttonPlay2.SetButtonType(ButtonType::Play);
	buttonPlay2.SetPosition({ 960,480 });
	buttonPlay2.SetOnClick(
		[]() {
			SceneGameplay& sceneGameplay = App::Get()->CreateOrGetScene<SceneGameplay>((size)SceneTag::Gameplay);
			sceneGameplay.LoadLevel(Level::Level2);
			sceneGameplay.SetActive(true);
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::LevelChoice).SetActive(false);
		}
	);

	GameText& textPlay3 = CreateGameObject<GameText>();
	textPlay3.SetPostion({ 1225,580 });
	textPlay3.SetText("Level 3");

	Button& buttonPlay3 = CreateGameObject<Button>();
	buttonPlay3.SetButtonType(ButtonType::Play);
	buttonPlay3.SetPosition({ 1310,480 });
	buttonPlay3.SetOnClick(
		[]() {
			SceneGameplay& sceneGameplay = App::Get()->CreateOrGetScene<SceneGameplay>((size)SceneTag::Gameplay);
			sceneGameplay.LoadLevel(Level::Level3);
			sceneGameplay.SetActive(true);
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::LevelChoice).SetActive(false);
		}
	);

	//////////////////////////////////////////////////

	GameText& textCustomize = CreateGameObject<GameText>();
	textCustomize.SetPostion({ 1140,775 });
	textCustomize.SetText("Customize");
	
	Button& buttonCustomize = CreateGameObject<Button>();
	buttonCustomize.SetButtonType(ButtonType::User);
	buttonCustomize.SetPosition({ 1250,700 });
	buttonCustomize.SetOnClick(
		[]() {
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Customisation).SetActive(true);
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::LevelChoice).SetActive(false);
		}
	);

	GameText& textGuide = CreateGameObject<GameText>();
	textGuide.SetPostion({ 610,775 });
	textGuide.SetText("Guide");

	Button& buttonGuide = CreateGameObject<Button>();
	buttonGuide.SetButtonType(ButtonType::Question);
	buttonGuide.SetPosition({ 670,700 });
	buttonGuide.SetOnClick(
		[]() {
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Guide).SetActive(true);
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::LevelChoice).SetActive(false);
		}
	);

	Button& buttonOptions = CreateGameObject<Button>();
	buttonOptions.SetButtonType(ButtonType::Cog);
	buttonOptions.SetPosition({ 1420,300 });
	buttonOptions.SetOnClick(
		[]() {
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Option).SetActive(true);
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::LevelChoice).SetActive(false);
			GameVariables::s_lastScene = SceneTag::LevelChoice;
		}
	);

	Button& buttonBackProfil = CreateGameObject<Button>();
	buttonBackProfil.SetButtonType(ButtonType::ReturnLeft);
	buttonBackProfil.SetPosition({ 500,300 });
	buttonBackProfil.SetOnClick(
		[]() {
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Profil).SetActive(true);
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::LevelChoice).SetActive(false);
		}
	);
}

void SceneLevelChoice::Destroy()
{
}

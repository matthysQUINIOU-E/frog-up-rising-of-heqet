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

	Button& buttonPlay = CreateGameObject<Button>();
	buttonPlay.SetButtonType(ButtonType::Play);
	buttonPlay.SetPosition({ 960,540 });
	buttonPlay.SetOnClick(
		[]() {
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Gameplay).SetActive(true);
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

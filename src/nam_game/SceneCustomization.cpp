#include "pch.h"
#include "SceneCustomization.h"
#include "BackgroudGreen.h"
#include "PlateWood.h"
#include "Button.h"
#include "GameText.h"
#include "SceneTag.h"
#include "GameVariables.h"

using namespace nam;

void SceneCustomization::Init()
{
	CreateGameObject<BackgroudGreen>();
	CreateGameObject<PlateWood>();

	GameText& title = CreateGameObject<GameText>();
	title.SetPostion({ 775,275 });
	title.SetText("Customization");
	title.SetTextSize(50);

	Button& buttonBack = CreateGameObject<Button>();
	buttonBack.SetButtonType(ButtonType::ReturnLeft);
	buttonBack.SetPosition({ 500,300 });
	buttonBack.SetOnClick(
		[]() {
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Customisation).SetActive(false);
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::LevelChoice).SetActive(true);
		}
	);

	Button& buttonOptions = CreateGameObject<Button>();
	buttonOptions.SetButtonType(ButtonType::Cog);
	buttonOptions.SetPosition({ 1420,300 });
	buttonOptions.SetOnClick(
		[]() {
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Option).SetActive(true);
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Customisation).SetActive(false);
			GameVariables::s_lastScene = SceneTag::Customisation;
		}
	);

	//TODO
}

void SceneCustomization::Destroy()
{
}

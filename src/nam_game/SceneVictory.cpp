#include "pch.h"
#include "SceneVictory.h"
#include "BackgroudGreen.h"
#include "PlateWood.h"
#include "Button.h"
#include "GameText.h"
#include "SceneTag.h"

using namespace nam;

void SceneVictory::Init()
{
	CreateGameObject<BackgroudGreen>();
	CreateGameObject<PlateWood>();

	GameText& title = CreateGameObject<GameText>();
	title.SetPostion({ 725,275 });
	title.SetText("Level finished !");
	title.SetTextSize(50);


	GameText& textP0 = CreateGameObject<GameText>();
	textP0.SetPostion({ 700,625 });
	textP0.SetText("Back to level choice");

	Button& buttonP0 = CreateGameObject<Button>();
	buttonP0.SetButtonType(ButtonType::List);
	buttonP0.SetPosition({ 960,540 });
	buttonP0.SetOnClick(
		[]() {
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::Victory).SetActive(false);
			App::Get()->CreateOrGetScene<Scene>((size)SceneTag::LevelChoice).SetActive(true);
		}
	);
}

void SceneVictory::Destroy()
{
}

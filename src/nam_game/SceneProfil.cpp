#include "pch.h"
#include "SceneProfil.h"
#include "BackgroudGreen.h"
#include "PlateWood.h"
#include "Button.h"
#include "GameText.h"

void SceneProfil::Init()
{
	CreateGameObject<BackgroudGreen>();
	CreateGameObject<PlateWood>();
	GameText& text = CreateGameObject<GameText>();
	text.SetPostion({ 100,100 });
	text.SetText("test hello world !");
	text.SetTextSize(100);
}

void SceneProfil::Destroy()
{
}

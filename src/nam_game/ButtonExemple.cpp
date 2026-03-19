#include "pch.h"
#include "ButtonExemple.h"
#include <SpriteManager.h>
#include <SceneTag.h>
#include <SceneGameplay.h>

using namespace nam;

void ButtonExemple::OnInit()
{
	SpriteRendererComponent src;
	src.mp_sprite = SpriteManager::GetSprite(SpriteTag::Button);
	TransformComponent transform;
	transform.SetWorldPosition({ 100,100,0 });
	AddComponent(src);
    AddComponent(transform);
	SetButton();
}

void ButtonExemple::OnClick()
{
	App::Get()->CreateOrGetScene<SceneGameplay>((size)SceneTag::Gameplay).SetActive(true);
	App::Get()->CreateOrGetScene<Scene>((size)SceneTag::LevelChoice).SetActive(false);
}

void ButtonExemple::OnHovered()
{
}

void ButtonExemple::OnLeft()
{
}

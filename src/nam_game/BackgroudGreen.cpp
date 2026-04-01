#include "pch.h"
#include "BackgroudGreen.h"
#include <SpriteManager.h>

using namespace nam;

void BackgroudGreen::OnInit()
{
	SpriteRendererComponent src;
	src.mp_sprite = SpriteManager::GetSprite(SpriteTag::BackgroundGreen);
	TransformComponent transform;
	transform.SetWorldPosition({ 960,540,0 });
	AddComponent(src);
	AddComponent(transform);
}

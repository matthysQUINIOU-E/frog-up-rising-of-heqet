#include "pch.h"
#include "PlateWood.h"

#include <SpriteManager.h>

using namespace nam;

void PlateWood::OnInit()
{
	SpriteRendererComponent src;
	src.mp_sprite = SpriteManager::GetSprite(SpriteTag::PlateWood);
	TransformComponent transform;
	transform.SetWorldPosition({ 960,540,0 });
	AddComponent(src);
	AddComponent(transform);
}

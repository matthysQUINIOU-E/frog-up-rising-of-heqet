#include "pch.h"
#include "SpriteManager.h"
#include <RenderManager.h>

using namespace nam;

std::array<bool, (size)SpriteTag::Size> SpriteManager::s_spritesInit = {};

Sprite* SpriteManager::GetSprite(SpriteTag spriteTag)
{
	if (s_spritesInit[(size)spriteTag] == false)
		return InitSprite(spriteTag);

	SpriteRendererComponent src;
	src.SetSpriteInstanceFromTag((size)spriteTag);
	return src.mp_sprite;
}

Sprite* SpriteManager::InitSprite(SpriteTag spriteTag)
{
	s_spritesInit[(size)spriteTag] = true;
	SpriteRendererComponent mrc;

	mrc.CreateSpriteInstance();
	mrc.SetSpriteTag((size)spriteTag);

	switch (spriteTag)
	{
	case SpriteTag::Button:
		mrc.mp_sprite->BuildRect({ 100,100 }, { 1,0,0,1 });
		break;
	default:
		mrc.mp_sprite->BuildRect({50,50},{1,1,1,1});
		break;
	}

	return mrc.mp_sprite;
}

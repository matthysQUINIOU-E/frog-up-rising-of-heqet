#include "pch.h"
#include "SpriteManager.h"
#include <RenderManager.h>
#include "TextureTag.h"

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
	case SpriteTag::ButtonCog0:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonCog0);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonLeft0:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonLeft0);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonRight0:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonRight0);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonReturnLeft0:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonReturnLeft0);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonReturnRight0:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonReturnRight0);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonTrash0:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonTrash0);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonUser0:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonUser0);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonValid0:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonValid0);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonX0:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonX0);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonQuestion0:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonQuestion0);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonPlay0:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonPlay0);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonList0:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonList0);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonCog1:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonCog1);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonLeft1:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonLeft1);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonRight1:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonRight1);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonReturnLeft1:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonReturnLeft1);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonReturnRight1:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonReturnRight1);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonTrash1:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonTrash1);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonUser1:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonUser1);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonValid1:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonValid1);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonX1:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonX1);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonQuestion1:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonQuestion1);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonPlay1:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonPlay1);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::ButtonList1:
		mrc.mp_sprite->BuildRect({ 114,114 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::ButtonList1);
		mrc.mp_sprite->m_drawLayer = 7;
		break;
	case SpriteTag::BackgroundGreen:
		mrc.mp_sprite->BuildRect({ 1920,1080 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::BackgroundGreen);
		mrc.mp_sprite->m_drawLayer = 9;
		break;
	case SpriteTag::PlateWood:
		mrc.mp_sprite->BuildRect({ 1280,720 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::PlateWood);
		mrc.mp_sprite->m_drawLayer = 8;
		break;
	case SpriteTag::Jauge5:
		mrc.mp_sprite->BuildRect({ 400,70 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::Jauge5);
		mrc.mp_sprite->m_drawLayer = 8;
		break;
	case SpriteTag::Jauge4:
		mrc.mp_sprite->BuildRect({ 400,70 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::Jauge4);
		mrc.mp_sprite->m_drawLayer = 8;
		break;
	case SpriteTag::Jauge3:
		mrc.mp_sprite->BuildRect({ 400,70 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::Jauge3);
		mrc.mp_sprite->m_drawLayer = 8;
		break;
	case SpriteTag::Jauge2:
		mrc.mp_sprite->BuildRect({ 400,70 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::Jauge2);
		mrc.mp_sprite->m_drawLayer = 8;
		break;
	case SpriteTag::Jauge1:
		mrc.mp_sprite->BuildRect({ 400,70 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::Jauge1);
		mrc.mp_sprite->m_drawLayer = 8;
		break;
	case SpriteTag::Jauge0:
		mrc.mp_sprite->BuildRect({ 400,70 }, { 1,1,1,1 });
		mrc.mp_sprite->SetTexture((size)TextureTag::Jauge0);
		mrc.mp_sprite->m_drawLayer = 8;
		break;
	default:
		mrc.mp_sprite->BuildRect({50,50},{1,1,1,1});
		break;
	}

	return mrc.mp_sprite;
}

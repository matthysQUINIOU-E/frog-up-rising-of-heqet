#pragma once
#include "SpriteTag.h"
#include "MeshTag.h"

class SpriteManager
{
public:
	static nam::Sprite* GetSprite(SpriteTag spriteTag);
private:
	static nam::Sprite* InitSprite(SpriteTag spriteTag);
private:
	static std::array<bool, (nam::size)SpriteTag::Size + (nam::size)MeshTag::Size> s_spritesInit;
};



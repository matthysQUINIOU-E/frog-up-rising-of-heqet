#include "pch.h"
#include "TextureLoader.h"
#include "TextureTag.h"

using namespace nam;

void TextureLoader::LoadAllTexture(nam::App* app)
{
    app->LoadTexture(L"../../res/Textures/dirt.dds", (size)TextureTag::Dirt);
    app->LoadTexture(L"../../res/Textures/grass.dds", (size)TextureTag::Grass);
}

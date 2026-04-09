#include "pch.h"
#include "TextureLoader.h"
#include "TextureTag.h"

using namespace nam;

void TextureLoader::LoadAllTexture(nam::App* app)
{
    app->LoadTexture(L"../../res/Textures/grass1.dds", (size)TextureTag::Grass1);
    app->LoadTexture(L"../../res/Textures/grass2.dds", (size)TextureTag::Grass2);
    app->LoadTexture(L"../../res/Textures/grass3.dds", (size)TextureTag::Grass3);
    app->LoadTexture(L"../../res/Textures/grass4.dds", (size)TextureTag::Grass4);
    app->LoadTexture(L"../../res/Textures/grass5.dds", (size)TextureTag::Grass5);
    app->LoadTexture(L"../../res/Textures/grass6.dds", (size)TextureTag::Grass6);
    app->LoadTexture(L"../../res/Textures/grass7.dds", (size)TextureTag::Grass7);
    app->LoadTexture(L"../../res/Textures/grass8.dds", (size)TextureTag::Grass8);
    app->LoadTexture(L"../../res/Textures/grass9.dds", (size)TextureTag::Grass9);
    app->LoadTexture(L"../../res/Textures/straw.dds", (size)TextureTag::Straw);
    app->LoadTexture(L"../../res/Textures/tile1.dds", (size)TextureTag::Tile1);
    app->LoadTexture(L"../../res/Textures/tile2.dds", (size)TextureTag::Tile2);
    app->LoadTexture(L"../../res/Textures/tile3.dds", (size)TextureTag::Tile3);
    app->LoadTexture(L"../../res/Textures/tile4.dds", (size)TextureTag::Tile4);
    app->LoadTexture(L"../../res/Textures/tile5.dds", (size)TextureTag::Tile5);
    app->LoadTexture(L"../../res/Textures/rockSoil.dds", (size)TextureTag::RockSoil);

    app->LoadTexture(L"../../res/Textures/backgroundGreen.dds", (size)TextureTag::BackgroundGreen);
    app->LoadTexture(L"../../res/Textures/plateWood.dds", (size)TextureTag::PlateWood);

    app->LoadTexture(L"../../res/Textures/Buttons/buttonCog0.dds", (size)TextureTag::ButtonCog0);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonCog1.dds", (size)TextureTag::ButtonCog1);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonLeft0.dds", (size)TextureTag::ButtonLeft0);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonLeft1.dds", (size)TextureTag::ButtonLeft1);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonList0.dds", (size)TextureTag::ButtonList0);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonList1.dds", (size)TextureTag::ButtonList1);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonPlay0.dds", (size)TextureTag::ButtonPlay0);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonPlay1.dds", (size)TextureTag::ButtonPlay1);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonQuestion0.dds", (size)TextureTag::ButtonQuestion0);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonQuestion1.dds", (size)TextureTag::ButtonQuestion1);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonReturnLeft0.dds", (size)TextureTag::ButtonReturnLeft0);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonReturnLeft1.dds", (size)TextureTag::ButtonReturnLeft1);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonReturnRight0.dds", (size)TextureTag::ButtonReturnRight0);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonReturnRight1.dds", (size)TextureTag::ButtonReturnRight1);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonRight0.dds", (size)TextureTag::ButtonRight0);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonRight1.dds", (size)TextureTag::ButtonRight1);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonTrash0.dds", (size)TextureTag::ButtonTrash0);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonTrash1.dds", (size)TextureTag::ButtonTrash1);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonUser0.dds", (size)TextureTag::ButtonUser0);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonUser1.dds", (size)TextureTag::ButtonUser1);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonValid0.dds", (size)TextureTag::ButtonValid0);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonValid1.dds", (size)TextureTag::ButtonValid1);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonX0.dds", (size)TextureTag::ButtonX0);
    app->LoadTexture(L"../../res/Textures/Buttons/buttonX1.dds", (size)TextureTag::ButtonX1);

    app->LoadTexture(L"../../res/Textures/Endurance-gauge/jauge0.dds", (size)TextureTag::Jauge0);
    app->LoadTexture(L"../../res/Textures/Endurance-gauge/jauge1.dds", (size)TextureTag::Jauge1);
    app->LoadTexture(L"../../res/Textures/Endurance-gauge/jauge2.dds", (size)TextureTag::Jauge2);
    app->LoadTexture(L"../../res/Textures/Endurance-gauge/jauge3.dds", (size)TextureTag::Jauge3);
    app->LoadTexture(L"../../res/Textures/Endurance-gauge/jauge4.dds", (size)TextureTag::Jauge4);
    app->LoadTexture(L"../../res/Textures/Endurance-gauge/jauge5.dds", (size)TextureTag::Jauge5);

    app->LoadTexture(L"../../res/Textures/Frog/FrogTexture.dds", (size)TextureTag::Frog1);
    app->LoadTexture(L"../../res/Textures/Frog/FrogTexture2.dds", (size)TextureTag::Frog2);
    app->LoadTexture(L"../../res/Textures/Collectible/Fly.dds", (size)TextureTag::Fly);

    app->LoadTexture(L"../../res/Textures/Environment/Pine.dds", (size)TextureTag::Pine);
    app->LoadTexture(L"../../res/Textures/Environment/LittlePine.dds", (size)TextureTag::LittlePine);
    app->LoadTexture(L"../../res/Textures/Environment/Rock.dds", (size)TextureTag::Rock);
    app->LoadTexture(L"../../res/Textures/Environment/TreeStump.dds", (size)TextureTag::TreeStump);
    app->LoadTexture(L"../../res/Textures/Environment/checkpoint.dds", (size)TextureTag::Checkpoint);
}

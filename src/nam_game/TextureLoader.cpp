#include "pch.h"
#include "TextureLoader.h"
#include "TextureTag.h"

using namespace nam;

void TextureLoader::LoadAllTexture(nam::App* app)
{
    app->LoadTexture(L"../../res/Textures/dirt.dds", (size)TextureTag::Dirt);
    app->LoadTexture(L"../../res/Textures/grass.dds", (size)TextureTag::Grass);
    app->LoadTexture(L"../../res/Textures/backgroundGreen.dds", (size)TextureTag::BackgroundGreen);

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
    app->LoadTexture(L"../../res/Textures/plateWood.dds", (size)TextureTag::PlateWood);

}

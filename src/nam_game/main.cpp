#include "pch.h"
#include "main.h"

#include "SceneTag.h"
#include "ColliderTag.h"
#include "MeshTag.h"
#include "TextureTag.h"

#include "SceneGameplay.h"
#include "SceneLevelChoice.h"

using namespace nam;
using namespace DirectX;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int cmdShow)
{
    App* app = App::Get(hInstance, 1920, 1080);
    app->LoadTexture(L"../../res/Textures/dirt.dds", (size)TextureTag::Dirt);
    app->LoadTexture(L"../../res/Textures/grass.dds", (size)TextureTag::Grass);

    SceneGameplay& scenegp = app->CreateOrGetScene<SceneGameplay>((size)SceneTag::Gameplay);
    scenegp.SetActive(false);

    SceneLevelChoice& scenelvlc = app->CreateOrGetScene<SceneLevelChoice>((size)SceneTag::LevelChoice);

  	app->Run();	
}
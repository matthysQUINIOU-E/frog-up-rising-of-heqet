#include "pch.h"
#include "SceneGameplay.h"
#include "Camera.h"
#include "MapLoader.h"
#include "Constant.h"

using namespace nam;
using namespace DirectX;

void SceneGameplay::Init()
{
}

void SceneGameplay::Destroy()
{
    Clear();
}

void SceneGameplay::LoadLevel(Level level)
{
    Destroy();

    Camera& camera = CreateGameObject<Camera>();

    switch (level)
    {
    case Level::Level1 :
        MapLoader::Load((std::string)LEVEL_1_FILE, this);
        break;
    case Level::Level2:
        MapLoader::Load((std::string)LEVEL_2_FILE, this);
        break;
    case Level::Level3:
        MapLoader::Load((std::string)LEVEL_3_FILE, this);
        break;
    }
}

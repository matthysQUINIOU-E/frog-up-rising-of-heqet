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

    switch (level) // TODO :: add other levels
    {
    case Level::Level1 :
        MapLoader::Load((std::string)LEVEL_1_FILE, this);
        break;
    default:
        MapLoader::Load((std::string)LEVEL_1_FILE, this);
    }
}

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

    // TODO :: make light load in map 
    GameObject& go = CreateGameObject<GameObject>();
    LightComponent lc;
    lc.CreateLightInstance();
    lc.mp_light->SetToDirectionalLight(0.8f, { 0.f,-1.f,0.f }, { 1.f,0.99f,0.88f });
    go.AddComponent<LightComponent>(lc);

    switch (level)
    {
    case Level::Level1 :
        MapLoader::Load((std::string)LEVEL_1_FILE, this);
        break;
    }
}

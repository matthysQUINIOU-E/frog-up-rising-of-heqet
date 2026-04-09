#include "pch.h"
#include "MapLoader.h"
#include <regex>
#include <fstream>
#include "Constant.h"
#include "Checkpoint.h"
#include "Platform.h"
#include "Frog1.h"
#include "Frog2.h"
#include "PressurePlate.h"
#include "MeshManager.h"

using namespace nam;
using namespace DirectX;

void MapLoader::Load(std::string file, nam::Scene* scene)
{
    std::ifstream f(std::string(SCENE_PATH) + file);
    nlohmann::json data;

    try {
        data = nlohmann::json::parse(f);
    }
    catch (const std::exception& e) {   
        std::cerr << "Erreur JSON: " << e.what() << std::endl;
        return;
    }

    if (!data.contains("objects") || !data["objects"].is_array())
        return;

    UnMap<u32, GameObject*> sceneObjects;

    for (auto& obj : data["objects"])
    {
        GameObjectFactory(scene, obj, sceneObjects);
    }
}

GameObject* MapLoader::GameObjectFactory(nam::Scene* scene, nlohmann::json_abi_v3_12_0::json& obj, UnMap<u32, GameObject*>& sceneObjects)
{
    GameObject* go = nullptr;

    MapLoaderFlag gameObjectFlag = MapLoaderFlagConvertor::StringToEnum(obj["gameobject"]);

    switch (gameObjectFlag)
    {
    case MapLoaderFlag::Checkpoint:
    {
        Checkpoint& c = scene->CreateGameObject<Checkpoint>();
        if (obj.contains("properties") && obj["properties"].is_object())
        {
            for (const auto& [key, value] : obj["properties"].items()) {
                MapLoaderFlag prop = MapLoaderFlagConvertor::StringToEnum(key);
                switch (prop)
                {
                case MapLoaderFlag::LevelEnd:
                    //TODO :: add feature
                    break;
                }
            }
        }
        go = &c;
        break;
    }

    case MapLoaderFlag::Intangible:
    {
        go = &scene->CreateGameObject<GameObject>();
        go->AddComponent<TransformComponent>({});
        if (obj.contains("properties") && obj["properties"].is_object())
        {
            for (const auto& [key, value] : obj["properties"].items()) {
                MapLoaderFlag prop = MapLoaderFlagConvertor::StringToEnum(key);
                switch (prop)
                {
                case MapLoaderFlag::Mesh:
                    MeshRendererComponent mrc;
                    mrc.mp_mesh = MeshManager::GetMesh(static_cast<MeshTag>(value.get<size_t>()));
                    go->AddComponent<MeshRendererComponent>(mrc);
                    break;
                }
            }
        }
        break;
    }

    case MapLoaderFlag::Dragonfly:
    {
        go = &scene->CreateGameObject<GameObject>(); // TODO :: create the right gameobject
        break;
    }

    case MapLoaderFlag::Frog1:
    {
        go = &scene->CreateGameObject<Frog1>();
        break;
    }

    case MapLoaderFlag::Frog2:
    {
        go = &scene->CreateGameObject<Frog2>();
        break;
    }

    case MapLoaderFlag::Grasshopper:
    {
        go = &scene->CreateGameObject<GameObject>(); // TODO :: create the right gameobject
        break;
    }

    case MapLoaderFlag::Platform:
    {
        Platform& platform = scene->CreateGameObject<Platform>();
        if (obj.contains("link") && !obj["link"].is_null())
        {
            GameObject* toLink = sceneObjects[obj["link"].get<u32>()];
            PressurePlate* toLinkCast = dynamic_cast<PressurePlate*>(toLink);
            if (toLinkCast != nullptr)
            {
                platform.SetEventListen(toLinkCast->GetEventId());
            }
        }
        if (obj.contains("properties") && obj["properties"].is_object())
        {
            for (const auto& [key, value] : obj["properties"].items()) {
                MapLoaderFlag prop = MapLoaderFlagConvertor::StringToEnum(key);
                switch (prop)
                {
                case MapLoaderFlag::Mesh:
                    platform.SetMesh(static_cast<MeshTag>(value.get<size_t>()));
                    break;
                case MapLoaderFlag::Speed:
                    platform.SetSpeed(value.get<float>());
                    break;
                case MapLoaderFlag::LoopWaypoints:
                    platform.LoopWaypoints(value.get<bool>());
                    break;
                case MapLoaderFlag::Waypoints:
                {
                    Vector<XMFLOAT3> waypoints;
                    for (const auto& point : value) {
                        if (point.is_array() && point.size() >= 3) {
                            float x = point[0].get<float>();
                            float y = point[1].get<float>();
                            float z = point[2].get<float>();
                            waypoints.emplace_back(x, y, z);
                        }
                    }
                    platform.SetWaypoints(waypoints);
                    break;
                }
                }
            }
        }
        go = &platform;
        break;
    }

    case MapLoaderFlag::PressurePlate:
    {
        PressurePlate& pressurePlate = scene->CreateGameObject<PressurePlate>();
       
        if (obj.contains("properties") && obj["properties"].is_object())
        {
            for (const auto& [key, value] : obj["properties"].items()) {
                MapLoaderFlag prop = MapLoaderFlagConvertor::StringToEnum(key);
                switch (prop)
                {
                case MapLoaderFlag::ToggleMode:
                    pressurePlate.SetToggleMode(value.get<bool>());
                    break;
                }
            }
        }
        go = &pressurePlate;
        break;
    }

    default:
        go = &scene->CreateGameObject<GameObject>();
    }

    XMFLOAT3 position;
    XMFLOAT4 rotation;
    XMFLOAT3 scale;

    position.x = obj["position"][0];
    position.y = obj["position"][2];
    position.z = obj["position"][1];

    rotation.x = obj["rotation"][0];
    rotation.y = obj["rotation"][1];
    rotation.z = obj["rotation"][2];
    rotation.w = obj["rotation"][3];

    scale.x = obj["scale"][0];
    scale.y = obj["scale"][1];
    scale.z = obj["scale"][2];

    if (!go->HasComponent<TransformComponent>())
        go->AddComponent<TransformComponent>({});
    TransformComponent& transform = go->GetComponent<TransformComponent>();
    transform.SetWorldPosition(position);
    transform.SetWorldRotation(rotation);
    transform.SetWorldScale(scale);

    if (obj["id"].is_number())
        sceneObjects[obj["id"]] = go;

    return go;
}

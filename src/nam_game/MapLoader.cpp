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
#include "GameLight.h"

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

GameObject* MapLoader::GameObjectFactory(Scene* scene, nlohmann::json_abi_v3_12_0::json& obj, UnMap<u32, GameObject*>& sceneObjects)
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
                    c.SetLevelEnd((bool)value.get<int>());
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
                case MapLoaderFlag::Texture:
                    platform.SetTexture(static_cast<TextureTag>(value.get<size_t>()));
                    break;
                case MapLoaderFlag::Speed:
                    platform.SetSpeed(value.get<float>());
                    break;
                case MapLoaderFlag::LoopWaypoints:
                    platform.LoopWaypoints((bool)value.get<int>());
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
                    pressurePlate.SetToggleMode((bool)value.get<int>());
                    break;
                }
            }
        }
        go = &pressurePlate;
        break;
    }

    case MapLoaderFlag::DirectionalLight:
    {
        float intensity = 1.f;
        XMFLOAT3 direction = { 0,-1,0 };
        XMFLOAT3 color = { 1,1,1 };

        if (obj.contains("properties") && obj["properties"].is_object())
        {
            for (const auto& [key, value] : obj["properties"].items()) {
                MapLoaderFlag prop = MapLoaderFlagConvertor::StringToEnum(key);
                switch (prop)
                {
                case MapLoaderFlag::Color:
                    if (value.is_array() && value.size() >= 3) {
                        color.x = value[0].get<float>();
                        color.y = value[1].get<float>();
                        color.z = value[2].get<float>();
                    }
                    break;
                case MapLoaderFlag::Direction:
                    if (value.is_array() && value.size() >= 3) {
                        direction.x = value[0].get<float>();
                        direction.y = value[1].get<float>();
                        direction.z = value[2].get<float>();
                    }
                    break;
                case MapLoaderFlag::Intensity:
                    intensity = value.get<float>();
                    break;
                }
            }
        }
        GameLight gl = scene->CreateGameObject<GameLight>();
        gl.SetToDirectional(intensity, direction, color);

        go = &gl;

        break;
    }

    case MapLoaderFlag::PointLight:
    {
        float intensity = 1.f;
        float range = 1.f;
        DirectX::XMFLOAT3 color = { 1,1,1 };

        if (obj.contains("properties") && obj["properties"].is_object())
        {
            for (const auto& [key, value] : obj["properties"].items()) {
                MapLoaderFlag prop = MapLoaderFlagConvertor::StringToEnum(key);
                switch (prop)
                {
                case MapLoaderFlag::Color:
                    if (value.is_array() && value.size() >= 3) {
                        color.x = value[0].get<float>();
                        color.y = value[1].get<float>();
                        color.z = value[2].get<float>();
                    }
                    break;
                case MapLoaderFlag::Range:
                    range = value.get<float>();
                    break;
                case MapLoaderFlag::Intensity:
                    intensity = value.get<float>();
                    break;
                }
            }
        }

        GameLight gl = scene->CreateGameObject<GameLight>();
        gl.SetToPoint(intensity, { 0,0,0 }, range, color);

        go = &gl;

        break;
    }

    case MapLoaderFlag::SpotLight:
    {
        float intensity = 1.f;
        float range = 1.f;
        XMFLOAT3 color = { 1,1,1 };
        XMFLOAT3 direction = { 0,-1,0 };
        float beginAngle = 1;
        float endAngle = 2;

        if (obj.contains("properties") && obj["properties"].is_object())
        {
            for (const auto& [key, value] : obj["properties"].items()) {
                MapLoaderFlag prop = MapLoaderFlagConvertor::StringToEnum(key);
                switch (prop)
                {
                case MapLoaderFlag::Color:
                    if (value.is_array() && value.size() >= 3) {
                        color.x = value[0].get<float>();
                        color.y = value[1].get<float>();
                        color.z = value[2].get<float>();
                    }
                    break;
                case MapLoaderFlag::Direction:
                    if (value.is_array() && value.size() >= 3) {
                        direction.x = value[0].get<float>();
                        direction.y = value[1].get<float>();
                        direction.z = value[2].get<float>();
                    }
                    break;
                case MapLoaderFlag::Range:
                    range = value.get<float>();
                    break;
                case MapLoaderFlag::Intensity:
                    intensity = value.get<float>();
                    break;
                case MapLoaderFlag::BeginAngle:
                    beginAngle = value.get<float>();
                    break;
                case MapLoaderFlag::EndAngle:
                    endAngle = value.get<float>();
                    break;
                }
            }
        }

        GameLight gl = scene->CreateGameObject<GameLight>();
        gl.SetToSpot(intensity, { 0,0,0 }, range, direction, beginAngle, endAngle, color);

        go = &gl;

        break;
    }

    case MapLoaderFlag::ParticuleEmiter:
    {
        go = &scene->CreateGameObject<GameObject>();
        go->AddComponent<TransformComponent>({});

        XMFLOAT3 minPos = { 0,0,0 };
        XMFLOAT3 maxPos = { 0,0,0 };
        XMFLOAT3 minDir = { -1,-1,-1 };
        XMFLOAT3 maxDir = { 1,1,1 };
        XMFLOAT3 startColor = { 1,1,1 };
        XMFLOAT3 endColor = { 1,1,1 };
        float minSpeed = 1.f;
        float maxSpeed = 1.f;
        float lifeTime = 30.f;
        float spawnRate = 1000.f;

        if (obj.contains("properties") && obj["properties"].is_object())
        {
            for (const auto& [key, value] : obj["properties"].items())
            {
                MapLoaderFlag prop = MapLoaderFlagConvertor::StringToEnum(key);
                switch (prop)
                {
                case MapLoaderFlag::MinPos:
                    if (value.is_array() && value.size() >= 3) {
                        minPos.x = value[0].get<float>();
                        minPos.y = value[1].get<float>();
                        minPos.z = value[2].get<float>();
                    }
                    break;
                case MapLoaderFlag::MaxPos:
                    if (value.is_array() && value.size() >= 3) {
                        maxPos.x = value[0].get<float>();
                        maxPos.y = value[1].get<float>();
                        maxPos.z = value[2].get<float>();
                    }
                    break;
                case MapLoaderFlag::MinDir:
                    if (value.is_array() && value.size() >= 3) {
                        minDir.x = value[0].get<float>();
                        minDir.y = value[1].get<float>();
                        minDir.z = value[2].get<float>();
                    }
                    break;
                case MapLoaderFlag::MaxDir:
                    if (value.is_array() && value.size() >= 3) {
                        maxDir.x = value[0].get<float>();
                        maxDir.y = value[1].get<float>();
                        maxDir.z = value[2].get<float>();
                    }
                    break;
                case MapLoaderFlag::StartColor:
                    if (value.is_array() && value.size() >= 3) {
                        startColor.x = value[0].get<float>();
                        startColor.y = value[1].get<float>();
                        startColor.z = value[2].get<float>();
                    }
                    break;
                case MapLoaderFlag::EndColor:
                    if (value.is_array() && value.size() >= 3) {
                        endColor.x = value[0].get<float>();
                        endColor.y = value[1].get<float>();
                        endColor.z = value[2].get<float>();
                    }
                    break;
                case MapLoaderFlag::MinSpeed:
                    minSpeed = value.get<float>();
                    break;
                case MapLoaderFlag::MaxSpeed:
                    maxSpeed = value.get<float>();
                    break;
                case MapLoaderFlag::LifeTime:
                    lifeTime = value.get<float>();
                    break;
                case MapLoaderFlag::SpawnRate:
                    spawnRate = value.get<float>();
                    break;
                }
            }
        }

        ParticleEmitersComponent pec;
        pec.AddEmiter(maxPos, minPos, maxDir, minDir, startColor, endColor, maxSpeed, minSpeed, lifeTime, spawnRate);
        go->AddComponent<ParticleEmitersComponent>(pec);

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
    rotation.y = obj["rotation"][2];
    rotation.z = obj["rotation"][1];
    rotation.w = obj["rotation"][3];

    scale.x = obj["scale"][0];
    scale.y = obj["scale"][2];
    scale.z = obj["scale"][1];

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
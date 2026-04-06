#include "pch.h"
#include "MapLoader.h"
#include <regex>
#include <fstream>
#include <Vertex.h>
#include "Constant.h"
#include "MeshManager.h"
#include "TextureTag.h"

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

    UnMap<u32, GameObject*> sceneObjects;

    for (auto& obj : data)
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
    case MapLoaderFlag::TEST1:
        break;
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

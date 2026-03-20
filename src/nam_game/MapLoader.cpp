#include "pch.h"
#include "MapLoader.h"
#include <regex>
#include <fstream>
#include <Vertex.h>
#include <json.h>
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

    std::regex patternPhysic("^[^_]*P");
    std::regex patternCollider("^[^_]*C");
    std::regex patternDestructible("^[^_]*D");
    std::regex patternNavMesh("^[^_]*NM");
    std::regex patternSpawnerHeal("^[^_]*SH");
    std::regex patternSpawnerGuHuoNiao("^[^_]*SG");
    std::regex patternSpawnerJiangshi("^[^_]*SJ");
    std::regex patternSpawnerMogwai("^[^_]*SM");

    Vector<Vertex> navmeshVertices;
    Vector<u32> navmeshIndices;

    for (auto& obj : data)
    {
        std::string type = obj.value("t", "NONE");
        if (type != "MESH")
            continue;

        std::string name = obj.value("n", "Unnamed");
        bool hasPhysic = std::regex_search(name, patternPhysic);
        bool hasCollider = std::regex_search(name, patternCollider);
        bool isDestructible = std::regex_search(name, patternDestructible);
        bool isNavMesh = std::regex_search(name, patternNavMesh);
        bool isSpawnerHeal = std::regex_search(name, patternSpawnerHeal);
        bool isSpawnerGuHuoNiao = std::regex_search(name, patternSpawnerGuHuoNiao);
        bool isSpawnerJiangshi = std::regex_search(name, patternSpawnerJiangshi);
        bool isSpawnerMogwai = std::regex_search(name, patternSpawnerMogwai);
        bool isobstacle = !isNavMesh && hasCollider;

        XMFLOAT3 position;
        XMFLOAT4 rotation;
        XMFLOAT3 scale;

        if (obj.contains("p"))
        {
            position.x = obj["p"][0];
            position.y = obj["p"][2];
            position.z = obj["p"][1];
        }

        if (obj.contains("r"))
            rotation = { obj["r"][0], obj["r"][2], obj["r"][1], obj["r"][3] };
        else
            rotation = { 0.f, 0.f, 0.f, 0.f };

        if (obj.contains("s"))
            scale = { obj["s"][0], obj["s"][2], obj["s"][1] };
        else
            scale = { 1.f, 1.f, 1.f };

        GameObject gameObject = scene->CreateGameObject<GameObject>(); // TODO :: change 
        
        if (gameObject.HasComponent<TransformComponent>())
        {
            TransformComponent& tc = gameObject.GetComponent<TransformComponent>();
            tc.SetWorldPosition(position);
            tc.SetWorldRotation(rotation);
            tc.SetWorldScale(scale);
        }



        if (hasCollider)
        {
            gameObject.SetBoxCollider();
        }

        if (hasCollider)
            gameObject.SetBoxCollider();

        if (hasPhysic)
            gameObject.AddComponent<PhysicComponent>({});

    }
}

#pragma once
#include <MapLoaderFlag.h>
#include <json.h>

class MapLoader
{
public:
	static void Load(std::string file, nam::Scene* scene);
	static nam::GameObject* GameObjectFactory(nam::Scene* scene, nlohmann::json_abi_v3_12_0::json& obj, nam::UnMap<nam::u32, nam::GameObject*>& sceneObjects);
};
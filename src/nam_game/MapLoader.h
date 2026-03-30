#pragma once
#include <MapLoaderFlag.h>

class MapLoader
{
public:
	static void Load(std::string file, nam::Scene* scene);
	static GameObject* GameObjectFactory(nam::Scene* scene, nlohmann::json_abi_v3_12_0::json& obj, nam::UnMap<u32, GameObject*>& sceneObjects);
};


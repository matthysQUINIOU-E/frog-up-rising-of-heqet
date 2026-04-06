#pragma once
#include <json.h>

class ConfigManager
{
public:
	static nlohmann::json GetConfig();
private:
	static void CreateConfig();
};


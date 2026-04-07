#pragma once
#include <json.h>

class SaveManager
{
public:
	static nlohmann::json GetSave();
private:
	static void CreateSave();
};


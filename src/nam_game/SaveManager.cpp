#include "pch.h"
#include "SaveManager.h"
#include "Constant.h"
#include <fstream>

nlohmann::json SaveManager::GetSave()
{
    std::ifstream f = std::ifstream(std::string(SAVE_PATH));
    if (!f.good())
        CreateSave();

    nlohmann::json data;

    try {
        data = nlohmann::json::parse(f);
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur JSON: " << e.what() << std::endl;
        return data;
    }

    return data;
}

void SaveManager::CreateSave()
{
    nlohmann::json data;

    data["profils"] = nlohmann::json::array();  

    for (size_t i = 0; i < 3; i++)
    {
        data["profils"][i] = {
            {"level1",
                {
                    {"time", 0},
                    {"completed", false},
                    {"collected", {50, 85, 75, 62}} // flies id exemple TODO remove
                }
            }
        };
    }

    std::ofstream out = std::ofstream(std::string(SAVE_PATH));

    if (out.is_open()) 
        out << data.dump(4);
    else 
        std::cerr << "Erreur : impossible d'écrire le fichier.\n";
    
}


#include "pch.h"
#include "ConfigManager.h"
#include "Constant.h"
#include <fstream>

nlohmann::json ConfigManager::GetConfig()
{
    std::ifstream f = std::ifstream(std::string(CONFIG_PATH));
    if (!f.good())
        CreateConfig();

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

void ConfigManager::CreateConfig()
{
    nlohmann::json data;

    data["profils"] = nlohmann::json::array();

    for (size_t i = 0; i < 3; i++)
    {
        data["profils"][i] = {
            {"customization", // later
                {
                    {"frog1Texture", 0}, // linked to enum
                    {"frog2Texture", 0}, // linked to enum
                    {"frog1Cosmetic", 0}, // linked to enum
                    {"frog2Cosmetic", 0} // linked to enum
                }
            },
            {"soundVolume", 0}, //later
        };
    }

    std::ofstream out = std::ofstream(std::string(CONFIG_PATH));

    if (out.is_open())
        out << data.dump(4);
    else
        std::cerr << "Erreur : impossible d'écrire le fichier.\n";
}

#include "pch.h"
#include "MapLoaderFlag.h"

MapLoaderFlag MapLoaderFlagConvertor::StringToEnum(std::string str)
{
    static std::unordered_map<std::string, MapLoaderFlag> map = {
        {"platform", MapLoaderFlag::Platform},
        {"intangible", MapLoaderFlag::Intangible},
        {"frog1", MapLoaderFlag::Frog1},
        {"frog2", MapLoaderFlag::Frog2},
        {"dragonfly", MapLoaderFlag::Dragonfly},
        {"grasshopper", MapLoaderFlag::Grasshopper},
        {"checkpoint", MapLoaderFlag::Checkpoint},
        {"pressurePlate", MapLoaderFlag::PressurePlate},
        {"mesh", MapLoaderFlag::Mesh},
        {"waypoints", MapLoaderFlag::Waypoints},
        {"speed", MapLoaderFlag::Speed},
        {"loopWaypoints", MapLoaderFlag::LoopWaypoints},
        {"toggleMode", MapLoaderFlag::ToggleMode},
        {"levelEnd", MapLoaderFlag::LevelEnd},
        {"directionalLight", MapLoaderFlag::DirectionalLight},
        {"color", MapLoaderFlag::Color},
        {"direction", MapLoaderFlag::Direction},
        {"intensity", MapLoaderFlag::Intensity},
        {"particuleEmiter", MapLoaderFlag::ParticuleEmiter},
        {"minPos", MapLoaderFlag::MinPos},
        {"maxPos", MapLoaderFlag::MaxPos},
        {"minDir", MapLoaderFlag::MinDir},
        {"maxDir", MapLoaderFlag::MaxDir},
        {"startColor", MapLoaderFlag::StartColor},
        {"endColor", MapLoaderFlag::EndColor},
        {"minSpeed", MapLoaderFlag::MinSpeed},
        {"maxSpeed", MapLoaderFlag::MaxSpeed},
        {"lifeTime", MapLoaderFlag::LifeTime},
        {"spawnRate", MapLoaderFlag::SpawnRate},
        {"pointLight", MapLoaderFlag::PointLight},
        {"range", MapLoaderFlag::Range},
        {"spotLight", MapLoaderFlag::SpotLight},
        {"beginAngle", MapLoaderFlag::BeginAngle},
        {"endAngle", MapLoaderFlag::EndAngle},
        {"texture", MapLoaderFlag::Texture}
    };
    auto it = map.find(str);
    return (it != map.end()) ? it->second : MapLoaderFlag::None;
}

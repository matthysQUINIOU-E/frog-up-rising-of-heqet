#include "pch.h"
#include "MapLoaderFlag.h"

MapLoaderFlag MapLoaderFlagConvertor::StringToEnum(std::string str)
{
    static std::unordered_map<std::string, MapLoaderFlag> map = {
        {"TEST1", MapLoaderFlag::TEST1}
    };
    auto it = map.find(str);
    return (it != map.end()) ? it->second : MapLoaderFlag::None;
}

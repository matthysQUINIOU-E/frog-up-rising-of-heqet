#pragma once
enum class MapLoaderFlag
{
	TEST1,
	None
};

class MapLoaderFlagConvertor
{
public:
	static MapLoaderFlag StringToEnum(std::string str);
};


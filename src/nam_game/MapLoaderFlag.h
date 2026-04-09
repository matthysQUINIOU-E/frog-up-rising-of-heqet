#pragma once

enum class MapLoaderFlag
{
	// Gameobject type
	Platform, // ##platform (can be linked to pressure plate plate to enable move on activation with #linkID)
	Intangible, // ##intangible
	Frog1, // ##frog1
	Frog2, // ##frog2
	Dragonfly, // ##dragonfly
	Grasshopper, // ##grasshopper
	Checkpoint, // ##checkpoint
	PressurePlate, // ##pressurePlate

	//other flags
	Mesh, // #mesh:1 (linked to MeshTag enum)
	Waypoints, // #waypoints:[[0,0,0],[0,5,0],[0,10,5]] (for mooving platforms)
	Speed, // #speed:2.5 (for mooving platforms)
	LoopWaypoints, // #loopWaypoints:1 (for mooving platforms)
	ToggleMode, // #toggleMode:0 (for pressure plate)
	LevelEnd, // #levelEnd:1 (for checkpoint)
	None
};

// exemple 20##platform#mesh:24#waypoints:[[0,0,0],[0,5,0],[0,10,5]]#link45
// 45##pressurePlate#toggleMode:0

class MapLoaderFlagConvertor
{
public:
	static MapLoaderFlag StringToEnum(std::string str);
};


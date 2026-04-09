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
	DirectionalLight, // ##directionalLight
	ParticuleEmiter, // ##particuleEmiter
	PointLight, // ##pointLight
	SpotLight, // ##spotLight

	//other flags
	Mesh, // #mesh:1 (linked to MeshTag enum)
	Waypoints, // #waypoints:[[0,0,0],[0,5,0],[0,10,5]] (for mooving platforms)
	Speed, // #speed:2.5 (for mooving platforms)
	LoopWaypoints, // #loopWaypoints:1 (for mooving platforms)
	ToggleMode, // #toggleMode:0 (for pressure plate)
	LevelEnd, // #levelEnd:1 (for checkpoint)
	Intensity, // #intensity:0.80 (used in directional light)
	Direction, // #direction:[0,-1,0] (used in directional light)
	Color, // #color:[1,1,1] (used in directional light)
	MinPos, // #minPos:[0,0,0] (used in particule emiter)
	MaxPos, // #maxPos:[0,0,0] (used in particule emiter)
	MinDir, // #minDir:[0,0,0] (used in particule emiter)
	MaxDir, // #maxDir:[0,0,0] (used in particule emiter)
	StartColor, // #startColor:[0,0,0] (used in particule emiter)
	EndColor, // #endColor:[0,0,0] (used in particule emiter)
	MinSpeed, // #minSpeed:5.5 (used in particule emiter)
	MaxSpeed, // #maxSpeed:10.5 (used in particule emiter)
	LifeTime, // #lifeTime:30 (used in particule emiter)
	SpawnRate, // #spawnRate:10000 (used in particule emiter)
	Range, // #range:5 (used in pointLight)
	BeginAngle, // #beginAngle:1 (used in spotLight)
	EndAngle, // #endAngle:2(used in spotLight)
	None
};

// exemple 20##platform#mesh:24#waypoints:[[0,0,0],[0,5,0],[0,10,5]]#link45
// 45##pressurePlate#toggleMode:0

class MapLoaderFlagConvertor
{
public:
	static MapLoaderFlag StringToEnum(std::string str);
};


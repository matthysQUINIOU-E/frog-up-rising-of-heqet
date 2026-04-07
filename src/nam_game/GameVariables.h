#pragma once
#include "SceneTag.h"

class GameVariables
{
public:
	static int s_currentProfile;
	static SceneTag s_lastScene; // useful only for some scene
	static bool s_isGamePaused;
};


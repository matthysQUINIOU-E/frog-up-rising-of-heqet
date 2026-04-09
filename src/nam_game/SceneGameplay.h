#pragma once
#include "Level.h"

class SceneGameplay : public nam::Scene
{
public:
	void Init() override;
	void Destroy() override;
	void LoadLevel(Level level);
};


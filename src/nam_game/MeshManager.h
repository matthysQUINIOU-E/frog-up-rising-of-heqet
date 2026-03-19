#pragma once
#include "MeshTag.h"

class MeshManager
{
public:
	static nam::Mesh* GetMesh(MeshTag meshTag);
private:
	static nam::Mesh* InitMesh(MeshTag meshTag);
private:
	static std::array<bool, (nam::size)MeshTag::Size> s_meshesInit;
};


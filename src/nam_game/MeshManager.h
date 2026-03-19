#pragma once
#include "MeshTag.h"

class MeshManager
{
public:
	MeshManager();
	~MeshManager();
	nam::Mesh* GetMesh(MeshTag meshTag);
private:
	nam::Mesh* InitMesh(MeshTag meshTag);
private:
	std::vector<bool> m_meshesInit;
};


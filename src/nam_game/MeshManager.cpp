#include "pch.h"
#include "MeshManager.h"
#include <RenderManager.h>

using namespace nam;
using namespace DirectX;

MeshManager::MeshManager()
{
    m_meshesInit.resize((size)MeshTag::Size);
}

MeshManager::~MeshManager()
{
}

Mesh* MeshManager::GetMesh(MeshTag meshTag)
{
	if (m_meshesInit[(size)meshTag] == false)
		return InitMesh(meshTag);

	return static_cast<Mesh*>(Render->GetRenderItemManager().GetRenderItemOfTag((size)meshTag));
}

Mesh* MeshManager::InitMesh(MeshTag meshTag)
{
	m_meshesInit[(size)meshTag] = true;
	MeshRendererComponent mrc;

	RenderItemManager& renderItemManager = Render->GetRenderItemManager();
	mrc.CreateMeshInstance();
	renderItemManager.SetRenderItemTag(mrc.mp_mesh, (size)meshTag);

	switch (meshTag)
	{
	case MeshTag::Frog1:
		break;
	case MeshTag::Frog2:
		break;
	default:
		break;
	}

	return nullptr;
}

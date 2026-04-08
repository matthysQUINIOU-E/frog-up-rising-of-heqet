#include "pch.h"
#include "MeshManager.h"
#include "TextureTag.h"
#include <RenderManager.h>

using namespace nam;

std::array<bool, (size)MeshTag::Size> MeshManager::s_meshesInit = {};

Mesh* MeshManager::GetMesh(MeshTag meshTag)
{
	if (s_meshesInit[(size)meshTag] == false)
		return InitMesh(meshTag);

	MeshRendererComponent mrc;
	mrc.SetMeshInstanceFromTag((size)meshTag);
	return mrc.mp_mesh;
}

Mesh* MeshManager::InitMesh(MeshTag meshTag)
{
	s_meshesInit[(size)meshTag] = true;
	MeshRendererComponent mrc;

	mrc.CreateMeshInstance();
	mrc.SetMeshTag((size)meshTag);

	switch (meshTag)
	{
	case MeshTag::Frog1:
		mrc.mp_mesh->LoadObj(L"../../res/Assets/Frog1/Frog.obj", { 1.f, 1.f, 1.f });
		mrc.mp_mesh->SetTexture((size)TextureTag::Frog1);
		break;
	case MeshTag::Frog2:
		mrc.mp_mesh->LoadObj(L"../../res/Assets/Frog2/Frog.obj", { 1.f, 1.f, 1.f });
		mrc.mp_mesh->SetTexture((size)TextureTag::Frog2);
		break;
	default:
		mrc.mp_mesh->BuildBox({ 1,1,1 }, { 1,1,1,1 });
		break;
	}

	return mrc.mp_mesh;
}

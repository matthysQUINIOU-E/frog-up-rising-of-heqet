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
	case MeshTag::Fly:
		mrc.mp_mesh->LoadObj(L"../../res/Assets/Collectible/Fly.obj", { 1.f, 1.f, 1.f });
		mrc.mp_mesh->SetTexture((size)TextureTag::Fly);
		break;
	case MeshTag::Spider:
		mrc.mp_mesh->LoadObj(L"../../res/Assets/Collectible/Spider.obj", { 1.f, 1.f, 1.f });
		mrc.mp_mesh->SetColor({ 0.15f, 0.15f, 0.15f, 1.f });
		break;
	case MeshTag::Dragonfly:
		mrc.mp_mesh->LoadObj(L"../../res/Assets/Collectible/DragonFly.obj", { 1.f, 1.f, 1.f });
		mrc.mp_mesh->SetColor({ 0.25f, 0.1f, 0.5f, 1.f });
		break;
	case MeshTag::Dinosaur:
		mrc.mp_mesh->LoadObj(L"../../res/Assets/Collectible/DINOSAUR.obj", { 1.f, 1.f, 1.f });
		mrc.mp_mesh->SetColor({ 0.25f, 0.25f, 0.25f, 1.f });
		break;
	case MeshTag::Grasshopper:
		mrc.mp_mesh->LoadObj(L"../../res/Assets/Collectible/Grasshopper.obj", { 1.f, 1.f, 1.f });
		mrc.mp_mesh->SetColor({ 0.25f, 0.75f, 0.25f, 1.f });
		break;
	case MeshTag::Pine:
		mrc.mp_mesh->LoadObj(L"../../res/Assets/Environment/Pine.obj", { 1.f, 1.f, 1.f });
		mrc.mp_mesh->SetTexture((size)TextureTag::Pine);
		break;
	case MeshTag::LittlePine:
		mrc.mp_mesh->LoadObj(L"../../res/Assets/Environment/LittlePine.obj", { 1.f, 1.f, 1.f });
		mrc.mp_mesh->SetTexture((size)TextureTag::LittlePine);
		break;
	case MeshTag::Rock:
		mrc.mp_mesh->LoadObj(L"../../res/Assets/Environment/Rock.obj", { 1.f, 1.f, 1.f });
		mrc.mp_mesh->SetTexture((size)TextureTag::Rock);
		break;
	case MeshTag::TreeStump:
		mrc.mp_mesh->LoadObj(L"../../res/Assets/Environment/TreeStump.obj", { 1.f, 1.f, 1.f });
		mrc.mp_mesh->SetTexture((size)TextureTag::TreeStump);
		break;
	case MeshTag::SmallPlatform:
		mrc.mp_mesh->LoadObj(L"../../res/Assets/Environment/SmallPlateform.obj", { 1.f, 1.f, 1.f });
		mrc.mp_mesh->SetColor({ 0.5f, 0.2f, 0.f, 1.f });
		break;
	case MeshTag::Platform:
		mrc.mp_mesh->LoadObj(L"../../res/Assets/Environment/Plateform.obj", { 1.f, 1.f, 1.f });
		mrc.mp_mesh->SetColor({ 0.5f, 0.2f, 0.f, 1.f });
		break;
	case MeshTag::GrassPlatform:
		mrc.mp_mesh->LoadObj(L"../../res/Assets/Environment/GrassPlateform.obj", { 1.f, 1.f, 1.f });
		mrc.mp_mesh->SetColor({ 0.5f, 0.5f, 0.f, 1.f });
		break;
	default:
		mrc.mp_mesh->BuildBox({ 1,1,1 }, { 1,1,1,1 });
		break;
	}

	return mrc.mp_mesh;
}

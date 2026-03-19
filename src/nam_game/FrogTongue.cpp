#include "pch.h"
#include "FrogTongue.h"

using namespace nam;
using namespace DirectX;

void FrogTongue::OnInit()
{
	MeshRendererComponent tongueMesh;
	tongueMesh.CreateMeshInstance();
	tongueMesh.mp_mesh->BuildBox({ 0.1f, 0.1f, 2.5f }, { 255.f, 105.f, 180.f, 1.0f });
	AddComponent<MeshRendererComponent>(tongueMesh);

	TransformComponent tongueTransform;
	tongueTransform.SetWorldScale({ 1.0f, 1.0f, 1.0f });
	AddComponent<TransformComponent>(tongueTransform);
}

void FrogTongue::OnUpdate()
{
	TransformComponent& tc = GetComponent<TransformComponent>();
}

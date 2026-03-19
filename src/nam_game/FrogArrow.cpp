#include "pch.h"
#include "FrogArrow.h"

using namespace nam;
using namespace DirectX;

void FrogArrow::OnInit()
{
    MeshRendererComponent arrowMesh;
    arrowMesh.CreateMeshInstance();
    arrowMesh.mp_mesh->LoadObj(L"../../res/Assets/Arrow/Arrow.obj", {1.f, 1.f, 1.f});
    AddComponent<MeshRendererComponent>(arrowMesh);

    TransformComponent arrowTransform;
    arrowTransform.SetWorldScale({ 0.7f, 0.7f, 1.5f });
    AddComponent<TransformComponent>(arrowTransform);
}

void FrogArrow::SetSlope(float slope)
{
    m_slope = slope;
    TransformComponent& tc = GetComponent<TransformComponent>();
    tc.SetLocalYPR(0.f, m_slope, 0.f);
}


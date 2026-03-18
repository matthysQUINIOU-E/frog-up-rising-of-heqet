#include "pch.h"
#include "FrogArrow.h"

using namespace nam;
using namespace DirectX;

void FrogArrow::OnInit()
{
    MeshRendererComponent arrowMesh;
    arrowMesh.CreateMeshInstance();
    arrowMesh.mp_mesh->BuildCylinder(0.3f, 10, 2.f, { 1.f, 1.f, 1.f, 1.f },{0.f, 0.f, 0.f}, {0.f, XM_PIDIV2, 0.f});
    AddComponent<MeshRendererComponent>(arrowMesh);

    TransformComponent arrowTransform;
    AddComponent<TransformComponent>(arrowTransform);
}

void FrogArrow::SetSlope(float slope)
{
    m_slope = slope;
}

#include "pch.h"
#include "FrogArrow.h"

using namespace nam;
using namespace DirectX;

void FrogArrow::OnInit()
{
    MeshRendererComponent arrowMesh;
    arrowMesh.CreateMeshInstance();
    arrowMesh.mp_mesh->BuildCone(0.1, 10, 1.f, { 1.f, 1.f, 1.f, 1.f });
    AddComponent<MeshRendererComponent>(arrowMesh);

    TransformComponent arrowTransform;
    arrowTransform.SetLocalYPR(0.f, -XM_PIDIV2, 0.f);
    AddComponent<TransformComponent>(arrowTransform);
}

void FrogArrow::SetSlope(float slope)
{
    m_slope = slope;
    TransformComponent& tc = GetComponent<TransformComponent>();
    tc.SetLocalYPR(0.f, -XM_PIDIV2 + m_slope, 0.f);


}


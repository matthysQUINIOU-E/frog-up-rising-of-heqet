#include "pch.h"
#include "FrogArrow.h"

using namespace nam;
using namespace DirectX;

void FrogArrow::OnInit()
{
    MeshRendererComponent arrowMesh;
    arrowMesh.CreateMeshInstance();
    arrowMesh.mp_mesh->BuildCylinder(0.1f, 10, 2.f, { 1.f, 1.f, 1.f, 1.f });
    AddComponent<MeshRendererComponent>(arrowMesh);

    TransformComponent arrowTransform;
    arrowTransform.SetWorldYPR(0.f, XM_PIDIV2, 0.f);
    AddComponent<TransformComponent>(arrowTransform);

}



void FrogArrow::SetSlope(float slope)
{
    m_slope = slope;
}

void FrogArrow::UpdateSlope(float slope)
{
    m_slope += slope;

    TransformComponent& tc = GetComponent<TransformComponent>();

    m_slope = std::clamp(m_slope, 0.f, m_maxSlope);

   tc.RotateLocalYPR(0.f, m_slope, 0.f);
}

#include "pch.h"
#include "GameLight.h"

using namespace nam;
using namespace DirectX;

void GameLight::OnInit()
{
}

void GameLight::OnDestroy()
{
    if (HasComponent<LightComponent>())
    {
        LightComponent& lc = GetComponent<LightComponent>();
        lc.DeleteLightInstance();
    }
}

void GameLight::SetToDirectional(float intensity, XMFLOAT3 direction, XMFLOAT3 color)
{
    LightComponent lc;
    lc.CreateLightInstance();
    lc.mp_light->SetToDirectionalLight(intensity, direction, color);
    AddComponent<LightComponent>(lc);
}

void GameLight::SetToPoint(float intensity, XMFLOAT3 position, float range, XMFLOAT3 color)
{
    AddComponent<TransformComponent>({});
    LightComponent lc;
    lc.CreateLightInstance();
    lc.mp_light->SetToPointLight(intensity, position, range, color);
    AddComponent<LightComponent>(lc);
}

void GameLight::SetToSpot(float intensity, DirectX::XMFLOAT3 position, float range, DirectX::XMFLOAT3 direction, float beginAngleRad, float endAngleRad, DirectX::XMFLOAT3 color)
{
    AddComponent<TransformComponent>({});
    LightComponent lc;
    lc.CreateLightInstance();
    lc.mp_light->SetToSpotLight(intensity, position, range, direction, beginAngleRad, endAngleRad, color);
    AddComponent<LightComponent>(lc);
}

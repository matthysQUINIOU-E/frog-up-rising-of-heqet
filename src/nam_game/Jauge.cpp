#include "pch.h"
#include "Jauge.h"
#include "SpriteManager.h"

using namespace nam;

void Jauge::OnInit()
{
    SpriteRendererComponent src;
    src.mp_sprite = SpriteManager::GetSprite(SpriteTag::Jauge5);
    TransformComponent transform;
    transform.SetWorldPosition({ 1705.f, 40.f, 0.f });
    AddComponent(src);
    AddComponent(transform);
}

void Jauge::SetJauge(JaugeType type)
{
    m_type = type;
    Update();
}

void Jauge::Update()
{
    if (m_previousType == m_type)
        return;

    SpriteRendererComponent& src = GetComponent<SpriteRendererComponent>();


    switch (m_type)
    {
    case JaugeType::Jauge5:
        src.mp_sprite = SpriteManager::GetSprite(SpriteTag::Jauge5);
        break;
    case JaugeType::Jauge4:
        src.mp_sprite = SpriteManager::GetSprite(SpriteTag::Jauge4);
        break;
    case JaugeType::Jauge3:
        src.mp_sprite = SpriteManager::GetSprite(SpriteTag::Jauge3);
        break;
    case JaugeType::Jauge2:
        src.mp_sprite = SpriteManager::GetSprite(SpriteTag::Jauge2);
        break;
    case JaugeType::Jauge1:
        src.mp_sprite = SpriteManager::GetSprite(SpriteTag::Jauge1);
        break;
    case JaugeType::Jauge0:
        src.mp_sprite = SpriteManager::GetSprite(SpriteTag::Jauge0);
        break;
    default:
        break;
    }

    m_previousType = m_type;
}
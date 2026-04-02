#include "pch.h"
#include "Jauge.h"
#include "SpriteManager.h"

using namespace nam;

void Jauge::OnInit()
{
    m_src.mp_sprite = SpriteManager::GetSprite(SpriteTag::Jauge5);
    TransformComponent transform;
    transform.SetWorldPosition({ 1500.f, 500.f, 0.f });
    AddComponent(m_src);
    AddComponent(transform);
}

void Jauge::SetJauge(JaugeType type)
{
    m_type = type;
}

void Jauge::Update()
{
    if (m_previousType == m_type)
        return;

    switch (m_type)
    {
    case JaugeType::Jauge5:
        m_src.mp_sprite = SpriteManager::GetSprite(SpriteTag::Jauge5);
        break;
    case JaugeType::Jauge4:
        m_src.mp_sprite = SpriteManager::GetSprite(SpriteTag::Jauge4);
        break;
    case JaugeType::Jauge3:
        m_src.mp_sprite = SpriteManager::GetSprite(SpriteTag::Jauge3);
        break;
    case JaugeType::Jauge2:
        m_src.mp_sprite = SpriteManager::GetSprite(SpriteTag::Jauge2);
        break;
    case JaugeType::Jauge1:
        m_src.mp_sprite = SpriteManager::GetSprite(SpriteTag::Jauge1);
        break;
    case JaugeType::Jauge0:
        m_src.mp_sprite = SpriteManager::GetSprite(SpriteTag::Jauge0);
        break;
    default:
        break;
    }

    m_previousType = m_type;
}
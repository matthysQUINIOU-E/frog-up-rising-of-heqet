#pragma once

#include "Frog.h"
#include "Swallow.h"

template<typename TagFrog>
inline bool Frog::CheckComponent()
{
    nam::Ecs& ecs = GetEcs();

    ecs.ForEach<TagFrog, nam::BoxColliderComponent, nam::TransformComponent, nam::PhysicComponent, Swallow>
        ([&](uint32_t entity, TagFrog& tag, nam::BoxColliderComponent& _collider, nam::TransformComponent& _transform, nam::PhysicComponent _physic, Swallow& _swallow)
        {
            m_otherFrogCollider = &_collider;
            m_otherFrogTransform = &_transform;
            m_otherFrogPhysic = &_physic;
            m_otherFrogSwallow = &_swallow;

        });

    return m_otherFrogCollider != nullptr && m_otherFrogSwallow != nullptr 
        && m_otherFrogTransform != nullptr && m_otherFrogPhysic != nullptr;

}
#include "pch.h"
#include "PressurePlate.h"
#include "EventRegister.h"

void PressurePlate::OnInit()
{
	m_eventId = EventRegister::GenerateId();
	
}

void PressurePlate::OnUpdate()
{
}

void PressurePlate::OnCollision(const nam::SingleCollisionInfo& self, const nam::SingleCollisionInfo& other)
{
}

uint32_t PressurePlate::GetEventId()
{
	return m_eventId;
}

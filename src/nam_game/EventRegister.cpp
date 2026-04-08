#include "pch.h"
#include "EventRegister.h"

nam::SparseSet<uint8_t> EventRegister::s_events = nam::SparseSet<uint8_t>(10000);
uint32_t EventRegister::s_lastId = 0;

void EventRegister::SetEvent(uint32_t id, bool val)
{
	if (id > s_lastId)
		s_lastId = id;
	if (!s_events.Add(id, (uint8_t)val))
		s_events.Get(id) = val;
}

bool EventRegister::GetEvent(uint32_t id)
{
	return s_events.Has(id) && s_events.Get(id);
}

uint32_t EventRegister::GenerateId()
{
	s_lastId++;
	return s_lastId;
}

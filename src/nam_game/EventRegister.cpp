#include "pch.h"
#include "EventRegister.h"

void EventRegister::SetEvent(uint32_t id, bool val)
{
	if (id > s_lastId)
		s_lastId = id;
	s_events.Add(id,(uint8_t)val);
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

#include "pch.h"
#include "EventRegister.h"

void EventRegister::SetEvent(uint32_t id, bool val)
{
	if (id > s_highestId)
		s_highestId = id;
	s_mapEvent[id] = val;
}

bool EventRegister::GetEvent(uint32_t id)
{
	auto it = s_mapEvent.find(id);
	if (it == s_mapEvent.end())
		return false;
	return it->second;
}

uint32_t EventRegister::GenerateId()
{
	s_highestId++;
	return s_highestId;
}

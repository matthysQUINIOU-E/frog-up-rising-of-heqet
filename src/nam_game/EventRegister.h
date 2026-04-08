#pragma once
class EventRegister
{
private:
	static nam::SparseSet<uint8_t> s_events;
	static uint32_t s_lastId;
public:
	static void SetEvent(uint32_t id, bool val);
	static bool GetEvent(uint32_t id);
	static uint32_t GenerateId();
};


#pragma once
class EventRegister
{
private:
	static std::unordered_map<uint32_t, bool> s_mapEvent;
	static uint32_t s_highestId; // not optimal can lead to bugs
public:
	static void SetEvent(uint32_t id, bool val);
	static bool GetEvent(uint32_t id);
	static uint32_t GenerateId();
};


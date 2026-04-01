#pragma once
// payload must be under 1024 bytes

enum class PayloadType : uint8_t
{
	CONNECT,
	PING,
	ACK
};

// payload cote reseau

struct PayloadConnect
{
};

struct PayloadPing
{
};

struct PayloadACK
{
	uint32_t packetToACKID;
};

// payload gameplay

#pragma once
class TCPSocket
{
public:
	TCPSocket();
	~TCPSocket();

	sockaddr_in GetSockAddrIn();

	bool Bind(uint16_t port = 1888, ULONG mask = INADDR_ANY);
	bool Listen();

	int Accept();

	bool Connect(sockaddr_in to);
	bool Connect(PCSTR ip, uint16_t port = 1888);

	bool Send(const Packet& buffer, uint16_t bufferSize);
	bool Send(const Packet& buffer, uint16_t bufferSize);
	bool Send(const uint8_t* buffer, uint16_t bufferSize);
	bool Send(const uint8_t* buffer, uint16_t bufferSize);

	Packet Receive(SOCKET from, uint16_t bufferSize);

private:
	SOCKET m_socket;
	sockaddr_in m_addr;
	std::unordered_map<SOCKET, sockaddr*> m_socketMap;
};
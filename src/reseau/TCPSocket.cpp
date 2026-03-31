#include "pch.h"
#include "TCPSocket.h"
#include <iostream>

TCPSocket::TCPSocket()
{
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
		std::cerr << "Erreur creation socket : " << WSAGetLastError() << std::endl;

	DWORD timeout = 100;
	if (setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) == SOCKET_ERROR)
	{
		std::cerr << "Erreur setsockopt SO_RCVTIMEO : " << WSAGetLastError() << std::endl;
	}
}

TCPSocket::~TCPSocket()
{
	closesocket(m_socket);
}

sockaddr_in TCPSocket::GetSockAddrIn()
{
	return m_addr;
}

bool TCPSocket::Bind(uint16_t port, ULONG mask)
{
	m_addr.sin_addr.s_addr = mask;
	m_addr.sin_port = htons(port);
	m_addr.sin_family = AF_INET;
	int res = bind(m_socket, (sockaddr*)(&m_addr), sizeof(m_addr));
	if (res != 0)
		return false;
	return true;
}

bool TCPSocket::Listen()
{
	int res = listen(m_socket, 5);
	if (res == SOCKET_ERROR)
		return false;
	return true;
}

int TCPSocket::Accept()
{
	sockaddr from;
	int clientSocket = accept(m_socket, &from, nullptr);
	m_socketMap[clientSocket] = &from;
	return clientSocket;
}


bool TCPSocket::Connect(sockaddr_in to)
{
	int res = connect(m_socket, (struct sockaddr*)&to, sizeof(to));
	if (res == SOCKET_ERROR)
		return false;
	return true;
}

bool TCPSocket::Connect(PCSTR ip, uint16_t port)
{
	sockaddr_in to;
	to.sin_addr.s_addr = inet_addr(ip);
	to.sin_family = AF_INET;
	to.sin_port = htons(port);
	return Connect(to);
}

bool TCPSocket::Send(const Packet& buffer, uint16_t bufferSize)
{
	return Send(buffer.data.data(), bufferSize);
}

bool TCPSocket::Send(const uint8_t* buffer, uint16_t bufferSize)
{
	int byteSent = send(m_socket, (char*)buffer, bufferSize, 0);
	if (byteSent == SOCKET_ERROR)
		return false;
	return true;
}

Packet TCPSocket::Receive(SOCKET from, uint16_t bufferSize)
{
	uint8_t* buffer;

	int res = recv(from, (char*)buffer, bufferSize, 0);
	if (res <= 0)
		return {};

	Packet packet;
	packet.data.resize(res);
	std::memcpy(packet.data.data(), buffer, res);
	packet.from = *(sockaddr_in*)m_socketMap[from];
	return packet;
}
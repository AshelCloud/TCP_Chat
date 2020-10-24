#pragma once

class TCPSocket
{
public:
	~TCPSocket();

public:
	int Connect(const SocketAddress& inAddress);
	int Bind(const SocketAddress& inAddress);
	int Listen(int inBackLog);
	shared_ptr<TCPSocket> Accept(SocketAddress& inFromAddress);
	int32_t	Send(const void* inData, int inLen);
	int32_t	Receive(void* inData, int inLen);

public:
	int SetNonBlockingMode(bool inShouldBeNonBlocking);

private:
	TCPSocket(SOCKET inSocket) : mSocket(inSocket) {}

private:
	SOCKET mSocket;

private:
	friend class SocketUtil;
};

using TCPSocketPtr = shared_ptr<TCPSocket>;
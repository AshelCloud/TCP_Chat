#include"Core.h"

TCPSocket::~TCPSocket()
{
	closesocket(mSocket);
}

int TCPSocket::Connect(const SocketAddress& inAddress)
{
	int err = connect(mSocket, &inAddress._sockAddr, inAddress.GetSize());
	if (err < 0)
	{
		std::cout << "TCPSocket::Connect Error" << std::endl;
		return -SocketUtil::GetLastError();
	}
	return NO_ERROR;
}

int TCPSocket::Bind(const SocketAddress& inAddress)
{
	int err = bind(mSocket, &inAddress._sockAddr, inAddress.GetSize());
	if (err < 0)
	{
		std::cout << "TCPSocket::Bind Error" << std::endl;
		return -SocketUtil::GetLastError();
	}
	return NO_ERROR;
}

int TCPSocket::Listen(int inBackLog)
{
	int err = listen(mSocket, inBackLog);
	if (err < 0)
	{
		std::cout << "TCPSocket::Listen Error" << std::endl;
		return -SocketUtil::GetLastError();
	}
	return NO_ERROR;
}

TCPSocketPtr TCPSocket::Accept(SocketAddress& inFromAddress)
{
	socklen_t length = inFromAddress.GetSize();
	SOCKET newSocket = accept(mSocket, &inFromAddress._sockAddr, &length);
	if (newSocket != INVALID_SOCKET)
	{
		return TCPSocketPtr(new TCPSocket(newSocket));
	}

	std::cout << "TCPSocket::Accept Error" << std::endl;
	return nullptr;
}

int32_t TCPSocket::Send(const void* inData, int inLen)
{
	int bytesSentCount = send(mSocket, static_cast<const char*>(inData), inLen, 0);
	if (bytesSentCount < 0)
	{
		std::cout << "TCPSocket::Send Error" << std::endl;
		return -SocketUtil::GetLastError();
	}
	return bytesSentCount;
}

int32_t TCPSocket::Receive(void* inData, int inLen)
{
	int bytesReceivedCount = recv(mSocket, static_cast<char*>(inData), inLen, 0);
	if (bytesReceivedCount < 0)
	{
		std::cout << "TCPSocket::Receive Error" << std::endl;
		return -SocketUtil::GetLastError();
	}
	return bytesReceivedCount;
}

int TCPSocket::SetNonBlockingMode(bool inShouldBeNonBlocking)
{
	u_long arg = inShouldBeNonBlocking ? 1 : 0;
	int result = ioctlsocket(mSocket, FIONBIO, &arg);

	if(result == SOCKET_ERROR)
	{
		std::cout << "TCPSocket::SetNonBolckingMode" << std::endl;
		return -SocketUtil::GetLastError();
	}
	
	return NO_ERROR;
}

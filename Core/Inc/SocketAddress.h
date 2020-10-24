#pragma once

class SocketAddress
{
public:
	SocketAddress()
	{
		GetAsSockAddrIn()->sin_family = AF_INET;
		GetAsSockAddrIn()->sin_addr.S_un.S_addr = INADDR_ANY;
		GetAsSockAddrIn()->sin_port = 0;
	}
	SocketAddress(uint32_t inAddress, uint16_t inPort)
	{
		GetAsSockAddrIn()->sin_family = AF_INET;
		GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(inAddress);
		GetAsSockAddrIn()->sin_port = htons(inPort);
	}
	SocketAddress(const sockaddr& inSockAddr)
	{
		memcpy(&_sockAddr, &inSockAddr, sizeof(sockaddr));
	}

	int GetSize() const { return sizeof(sockaddr); }

private:
	sockaddr _sockAddr;

private:
	sockaddr_in* GetAsSockAddrIn()
	{
		return reinterpret_cast<sockaddr_in*>(&_sockAddr);
	}

private:
	friend class TCPSocket;
};

using SocketAddressPtr = shared_ptr<SocketAddress>;
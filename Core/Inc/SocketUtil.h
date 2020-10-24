#pragma once

enum class SocketAddressFamily
{
	INET = AF_INET,
	INET6 = AF_INET6
};


class SocketUtil
{
public:
	static bool StaticInit();
	static void CleanUp();

public:
	static fd_set* FillSetFromVector(fd_set& outSet, const vector<TCPSocketPtr>* inSockets);
	static void FillVectorFromSet(vector<TCPSocketPtr>* outSockets, const vector<TCPSocketPtr>* inSockets, const fd_set& inSet);
	static int Select(const vector<TCPSocketPtr>* inReadSet, vector<TCPSocketPtr>* outReadSet,
						const vector<TCPSocketPtr>* inWriteSet, vector<TCPSocketPtr>* outWriteSet, 
						const vector<TCPSocketPtr>* inExceptSet, vector<TCPSocketPtr>* outExcepSet);
public:
	static int GetLastError();
public:
	static TCPSocketPtr CreateTCPSocket(SocketAddressFamily inFamily);
};
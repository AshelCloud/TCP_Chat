#include<Core.h>

int main()
{
	bool res = SocketUtil::StaticInit();
	if (res == false)
	{
		return 0;
	}

	TCPSocketPtr listenSocket = SocketUtil::CreateTCPSocket(SocketAddressFamily::INET);
	SocketAddress servAddr(INADDR_ANY, 9426);

	if(listenSocket->Bind(servAddr) != NO_ERROR)
	{
		return 0;
	}

	listenSocket->Listen(5);

	vector<TCPSocketPtr> readBlockSockets;
	readBlockSockets.push_back(listenSocket);
	vector<TCPSocketPtr> readableSockets;

	map<int, TCPSocketPtr> clntSockets;

	while(true)
	{
		if(SocketUtil::Select(&readBlockSockets, &readableSockets, nullptr, nullptr, nullptr, nullptr) == -1)
		{
			continue;
		}

		for(const TCPSocketPtr& socket : readableSockets)
		{
			if(socket == listenSocket)
			{
				SocketAddress clntAddr;
				TCPSocketPtr newSocket = listenSocket->Accept(clntAddr);
				readBlockSockets.push_back(newSocket);
				clntSockets.emplace(clntSockets.size(), newSocket);
			}
			else
			{
				char segment[512]{};

				int dataReceived = socket->Receive(segment, sizeof(segment));

				for(const std::pair<int, TCPSocketPtr>& clnt : clntSockets)
				{
					if(clnt.second == socket) { continue; }

					string msg = std::to_string(clnt.first) + ": ";
					msg += segment;

					clnt.second->Send(msg.c_str(), sizeof(segment));
				}
			}
		}
	}

	SocketUtil::CleanUp();

	return 0;
}
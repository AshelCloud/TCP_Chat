#include<Core.h>
#include<thread>

void SendThread(const TCPSocketPtr& clntSocket)
{
	while(true)
	{
		char msg[512];

		std::cin >> msg;
		clntSocket->Send(msg, strlen(msg) + 1);
	}
}

void ReceiveThread(const TCPSocketPtr& clntSocket)
{
	while(true)
	{
		char msg[512];

		clntSocket->Receive(msg, sizeof(msg));
		std::cout << msg << std::endl;
	}
}

int main()
{
	bool res = SocketUtil::StaticInit();
	if(res == false)
	{
		SocketUtil::CleanUp();
		return 0;
	}

	TCPSocketPtr clntSocket = SocketUtil::CreateTCPSocket(SocketAddressFamily::INET);

	SocketAddressPtr servAddr;
	servAddr = SocketAddressFactory::CreateIPv4FromString("127.0.0.1:9426");

	int err = clntSocket->Connect(*servAddr);

	std::thread sendThread(SendThread, clntSocket);
	std::thread receiveThread(ReceiveThread, clntSocket);

	sendThread.join();
	receiveThread.join();

	SocketUtil::CleanUp();

	return 0;
}
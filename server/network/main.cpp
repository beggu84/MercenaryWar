#include "Network.h"

#include "TcpServer.h"

int _tmain(int argc, _TCHAR* argv[])
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	TcpServer* tcpServer = new TcpServer(8081, sysInfo.dwNumberOfProcessors, 16384);
	tcpServer->Start();

	while (true)
	{
		char* message = NULL;
		while ((message = tcpServer->GetProactor()->PopMessage()) != NULL)
		{
			//printf("message received. packetType=%d, packetSize=%d\n", *(UINT16*)&message[1], *(UINT16*)&message[7]);
		}
		Sleep(1);
	}

	return 0;
}
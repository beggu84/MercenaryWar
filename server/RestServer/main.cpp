#include "stdafx.h"

#include "RestServer.h"

#include <MyLogger.h>

using namespace std;
using json = nlohmann::json;

struct RestServerSettings
{
	std::string version;
	WORD port;
	std::string nosqlUrl;
	SecureLevel secureLevel;

	RestServerSettings()
	{
		port = 0;
		secureLevel = SecureLevel::BASIC;
	}
};

static UINT WINAPI ThreadProc(void* argList)
{
	RestServerSettings* settings = (RestServerSettings*)argList;

	RestServer restServer;
	restServer.Setup(settings->version, settings->port, settings->secureLevel);
	restServer.ConnnectNoSQL(settings->nosqlUrl);
	restServer.Run();
	restServer.Cleanup();

	return 0;
}

int main(int argc, char* argv[])
{
	MyLogger::Initialize("restserver");

	RestServer restServer;
	restServer.Setup(REST_SERVER_VERSION, REST_SERVER_PORT, SecureLevel::BASIC);
	restServer.ConnnectNoSQL(REST_SERVER_NOSQL_URL);
	restServer.Run();
	restServer.Cleanup();

	MyLogger::Close();

	/*
	RestServerSettings httpServer;
	httpServer.version = REST_SERVER_VERSION;
	httpServer.port = REST_SERVER_PORT;
	httpServer.nosqlUrl = REST_SERVER_NOSQL_URL;
	httpServer.useSSL = false;
	httpServer.useEncryption = false;
	unsigned int httpServerThreadId;
	_beginthreadex(NULL, 0, ThreadProc, (void*)&httpServer, 0, &httpServerThreadId);

	RestServerSettings httpsServer;
	httpsServer.version = REST_SERVER_VERSION;
	httpsServer.port = REST_SERVER_PORT + 1;
	httpsServer.nosqlUrl = REST_SERVER_NOSQL_URL;
	httpsServer.useSSL = true;
	httpsServer.useEncryption = false;
	unsigned int httpsServerThreadId;
	_beginthreadex(NULL, 0, ThreadProc, (void*)&httpsServer, 0, &httpsServerThreadId);

	while(true)
	{
		Sleep(100);
	}
	*/

	return 0;
}

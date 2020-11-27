#pragma once

class WinsockBase
{
public:
	WinsockBase()
	{
		WSADATA	wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{
		}
	}

	virtual ~WinsockBase()
	{
		WSACleanup();
	}
};
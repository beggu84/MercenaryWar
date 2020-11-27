#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#ifndef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS 1
#endif

#include "MyLogger.h"

#include <libcouchbase/couchbase++.h>

class ServerBase
{
protected:
	std::string _version;
	WORD _port;

	float _updatePerSecond;
	float _updateIntervalTime;
	float _displayIntervalTime;

protected:
	Couchbase::Client* _noSQL;
	CRITICAL_SECTION _noSQLCS;

public:
	ServerBase();
	virtual ~ServerBase();

	virtual void Cleanup() = 0;
	virtual void Run() = 0;

	virtual bool ConnnectNoSQL(const std::string& url);
	virtual Couchbase::GetResponse GetNoSQLNode(const std::string& key);
	virtual Couchbase::StoreResponse SetNoSQLNode(const std::string& key, const std::string& value);

	void SetUpdatePerSecond(float targetUPS);
	void SetDisplayInterval(float interval);

protected:
	virtual void SetupMessageHandler() = 0;
};

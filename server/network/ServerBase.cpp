#include "stdafx.h"
#include "ServerBase.h"

#include "Global.h"

#include <cmath>

ServerBase::ServerBase()
{
	_noSQL = NULL;
	::InitializeCriticalSection(&_noSQLCS);

	SetUpdatePerSecond(1);
	SetDisplayInterval(5.0f);
}

ServerBase::~ServerBase()
{
	::DeleteCriticalSection(&_noSQLCS);
	SAFE_DELETE(_noSQL);
}

bool ServerBase::ConnnectNoSQL(const std::string& url)
{
	_noSQL = new Couchbase::Client(url);
	Couchbase::Status res = _noSQL->connect();
	if (!res.success())
	{
		//LOG(FATAL) << "Couldn't connect to '" << url << "'. " << "Reason: " << res;
		return false;
	}

	//LOG(INFO) << "Connecting couchbase database is succeeded. url=" << url;
	return true;
}

Couchbase::GetResponse ServerBase::GetNoSQLNode(const std::string& key)
{
	::EnterCriticalSection(&_noSQLCS);

	Couchbase::GetResponse res;

	int i = 0;
	do
	{
		res = _noSQL->get(key);

		i++;
		if (i >= 5)
			break;

		if (res.status().isTemporary() || res.status().errcode() == LCB_ETMPFAIL)
		{
			int backoffexp = i + 4;
			double backoffMillis = pow(2, backoffexp);
			backoffMillis = __min(1000.0, backoffMillis);
			LOG_ERROR("[Get] couchbase temporary error. Sleep {0:f} milliseconds", backoffMillis);
			Sleep(backoffMillis);
		}
		else
		{
			break;
		}
	} while (true);

	::LeaveCriticalSection(&_noSQLCS);

	return res;
}

Couchbase::StoreResponse ServerBase::SetNoSQLNode(const std::string& key, const std::string& value)
{
	::EnterCriticalSection(&_noSQLCS);

	Couchbase::StoreResponse res;

	int i = 0;
	do
	{
		res = _noSQL->upsert(key, value);

		i++;
		if (i >= 5)
			break;

		if (res.status().isTemporary() || res.status().errcode() == LCB_ETMPFAIL)
		{
			int backoffexp = i + 4;
			double backoffMillis = pow(2, backoffexp);
			backoffMillis = __min(1000.0, backoffMillis);
			LOG_ERROR("[Set] couchbase temporary error. Sleep {0:f} milliseconds", backoffMillis);
			Sleep(backoffMillis);
		}
		else
		{
			break;
		}
	} while (true);

	::LeaveCriticalSection(&_noSQLCS);

	return res;
}

void ServerBase::SetUpdatePerSecond(float targetUPS)
{
	if (targetUPS < 0.1f)
		targetUPS = 0.1f;

	_updatePerSecond = targetUPS;
	_updateIntervalTime = (1.0f / targetUPS);
}

void ServerBase::SetDisplayInterval(float interval)
{
	_displayIntervalTime = interval;
}
#include "stdafx.h"
#include "RestServer.h"

#include "UniqueIdGenerator.h"

#include <HttpDownloader.h>
#include <Encoder.h>
#include <JsonHelper.h>
#include <RandomHelper.h>

#define REST_SERVER_HTTPS_CRT	"https.crt"
#define REST_SERVER_HTTPS_KEY	"https.key"
#define REST_SERVER_AES_KEY		"C++ is awesome!!" // 16 characters

using namespace std;
using namespace fastdelegate;
using json = nlohmann::json;

RestServer::RestServer()
{
}

RestServer::~RestServer()
{
}

bool RestServer::Setup(const std::string& version, WORD port, SecureLevel secureLevel)
{
	if (secureLevel == SecureLevel::AES)
		_encoder->GenerateAesKey(REST_SERVER_AES_KEY);

	if (!WebServer::Setup(version, port, secureLevel))
		return false;

	_crow.route_dynamic("/redirect").methods(crow::HTTPMethod::Get)
		([this](const crow::request& req) {

		return crow::response(200);
	});

	//chrono::milliseconds refrechInterval(1800 * 1000); // 30 minutes
	//_crow.tick(refrechInterval, [this]()
	//{
	//});

	_itemIdGenerator = new UniqueIdGenerator();
	_itemIdGenerator->Setup();

	::InitializeCriticalSection(&_idGenCS);

	return true;
}

void RestServer::SetupMessageHandler()
{
	AddHandlerFunction("version", MakeDelegate(this, &RestServer::OnRecvVersion));
}

void RestServer::Cleanup()
{
	::DeleteCriticalSection(&_idGenCS);

	WebServer::Cleanup();
}

void RestServer::Run()
{
	if (_secureLevel == SecureLevel::SSL)
		_crow.port(_port).ssl_file(REST_SERVER_HTTPS_CRT, REST_SERVER_HTTPS_KEY).multithreaded().run();
	else
		_crow.port(_port).multithreaded().run();
}

bool RestServer::ConnnectNoSQL(const std::string& url)
{
	bool res = WebServer::ConnnectNoSQL(url);
	if (!res)
		return false;

	::EnterCriticalSection(&_idGenCS);
	auto userIdGen = GetNoSQLNode(USER_ID_GENERATOR);
	if (userIdGen.status().isDataError())
	{
		SetNoSQLNode(USER_ID_GENERATOR, "0");
		userIdGen = GetNoSQLNode(USER_ID_GENERATOR);
	}
	::LeaveCriticalSection(&_idGenCS);
	LOG_INFO("userCount: {0:s}", userIdGen.value().to_string());

	return true;
}

bool RestServer::OnRecvVersion(const json& r, json& w)
{
	w =
	{
		{ "is_success", true },
		{ "version_no", REST_SERVER_VERSION }
	};

	return true;
}

int64_t RestServer::NextGenerateItemId() const
{
	return _itemIdGenerator->Next();
}

int32_t RestServer::GeneratePlayerId()
{
	::EnterCriticalSection(&_idGenCS);
	auto userIdGen = GetNoSQLNode(USER_ID_GENERATOR);
	int32_t count = std::stoi(userIdGen.value().to_string());
	++count;
	SetNoSQLNode(USER_ID_GENERATOR, to_string(count));
	::LeaveCriticalSection(&_idGenCS);
	return count;
}

string RestServer::GetPlayerKey(int32_t playerId)
{
	return string();
	//return boost::str(boost::format("user_%d") % playerId);
}

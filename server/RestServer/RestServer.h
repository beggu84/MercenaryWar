#pragma once

#include <WebServer.h>

#include "LogMacros.h"

#define REST_SERVER_VERSION			"0.0.1"
#define REST_SERVER_PORT			4832
#define REST_SERVER_NOSQL_URL		"couchbase://localhost/roguehearts"
#define REST_SERVER_REDIRECT_URL	"http://ninetail.gonetis.com"

class UniqueIdGenerator;

class RestServer : public WebServer
{
public:
	RestServer();
	~RestServer();

private:
	const std::string USER_ID_GENERATOR = "USER_ID_GENERATOR";
	const std::string CHARACTER_ID_GENERATOR = "CHARACTER_ID_GENERATOR";

private:
	CRITICAL_SECTION _idGenCS;

	UniqueIdGenerator* _itemIdGenerator{ nullptr };

public:
	bool Setup(const std::string& version, WORD port, SecureLevel secureLevel) override;
	void Cleanup() override;
	void Run() override;
	bool ConnnectNoSQL(const std::string& url) override;

	int64_t NextGenerateItemId() const;

	std::string GetPlayerKey(int32_t playerId);

protected:
	void SetupMessageHandler() override;

	bool OnRecvVersion(const nlohmann::json& r, nlohmann::json& w);

private:
	int32_t GeneratePlayerId();
};

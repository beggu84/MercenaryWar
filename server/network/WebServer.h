#pragma once

#include "ServerBase.h"

#include <crow/crow.h>
#include <json.hpp>
#include <FastDelegate.h>

//#ifndef CROW_MSVC_WORKAROUND
//#define CROW_MSVC_WORKAROUND 1
//#endif

class HttpDownloader;
class Encoder;

enum class SecureLevel
{
	BASIC=0, AES, SSL
};

class WebServer : public ServerBase
{
public:
	using MessageHandlerDelegate = fastdelegate::FastDelegate2<const nlohmann::json&, nlohmann::json&, bool>;
	using MessageHandlerMap = std::map<std::string, MessageHandlerDelegate>;

protected:
	crow::SimpleApp _crow;
	MessageHandlerMap _handlerMap;

	SecureLevel _secureLevel;
	HttpDownloader* _httpDownloader;
	Encoder* _encoder;

public:
	WebServer();
	virtual ~WebServer();

	virtual bool Setup(const std::string& version, WORD port, SecureLevel secureLevel);
	void Cleanup() override;
	void Run() override;

	bool AddHandlerFunction(const std::string& name, MessageHandlerDelegate func);
	virtual bool MessageHandler(const std::string& name, const nlohmann::json& r, nlohmann::json& w);

private:
	virtual const nlohmann::json JsonParse(const std::string& str);
	virtual const std::string JsonDump(const nlohmann::json& j);
};

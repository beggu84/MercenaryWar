#include "WebServer.h"

#include <memory>

#include "HttpDownloader.h"
#include "Encoder.h"
#include "MessageAgentBase.h"
#include "TableBase.h"
#include "JsonHelper.h"
#include "MyLogger.h"

using namespace std;
using json = nlohmann::json;

class CrowLogHandler : public crow::ILogHandler 
{
public:
	void log(std::string message, crow::LogLevel level) override 
	{
		switch (level)
		{
		case crow::LogLevel::DEBUG:
			LOG_DEBUG(message);
			break;
		case crow::LogLevel::INFO:
			LOG_INFO(message);
			break;
		case crow::LogLevel::WARNING:
			LOG_WARNING(message);
			break;
		case crow::LogLevel::ERROR:
			LOG_ERROR(message);
			break;
		case crow::LogLevel::CRITICAL:
			LOG_CRITICAL(message);
			break;
		}
	}
};

WebServer::WebServer()
{
	_httpDownloader = new HttpDownloader();
	_encoder = new Encoder();
}

WebServer::~WebServer()
{
	SAFE_DELETE(_encoder);
}

bool WebServer::Setup(const string& version, WORD port, SecureLevel secureLevel)
{
	_version = version;
	_port = port;
	_secureLevel = secureLevel;

	crow::logger::setLogLevel(crow::LogLevel::WARNING);
	crow::logger::setHandler(new CrowLogHandler()); // TODO : RESOLVE MEMORY LEAK

	_crow.route_dynamic("/api").methods(crow::HTTPMethod::Post)
	([this](const crow::request& req) {
		json r = JsonParse(req.body);

		string name;
		if(!JsonHelper::GetStringField(r, "name", name))
			return crow::response(400);

		json w;
		if (!this->MessageHandler(name, r, w))
			return crow::response(400);

		return crow::response(JsonDump(w));
	});

	SetupMessageHandler();

	return true;
}

void WebServer::Cleanup()
{
	crow::logger::setHandler(NULL);
}

void WebServer::Run()
{
	_crow.port(_port).multithreaded().run();
}

bool WebServer::AddHandlerFunction(const string& name, MessageHandlerDelegate func)
{
	if (name.empty() || func == NULL)
		return false;
	
	MessageHandlerMap::iterator itor = _handlerMap.find(name);
	if (itor != _handlerMap.end()) // already added
		return false;

	_handlerMap.insert(make_pair(name, func));

	return true;
}

bool WebServer::MessageHandler(const string& name, const json& r, json& w)
{
	try
	{
		MessageHandlerMap::iterator itor = _handlerMap.find(name);
		if (itor != _handlerMap.end())
		{
			return ((*itor).second)(r, w);
		}
	}
	catch (std::exception& e)
	{
		LOG_ERROR("[EXCEPTION] {0:s}", e.what());
		return false;
	}
	catch (...)
	{
		return false;
	}

	return false;
}

const json WebServer::JsonParse(const string& str)
{
	if (_secureLevel == SecureLevel::AES)
	{
		string decipheredText;
		_encoder->Decode(str, decipheredText);
		return json::parse(decipheredText);
	}
	else
	{
		return json::parse(str);
	}
}

const string WebServer::JsonDump(const json& j)
{
	if (_secureLevel == SecureLevel::AES)
	{
		string cipheredText;
		_encoder->Encode(j.dump(), cipheredText);
		return cipheredText;
	}
	else
	{
		return j.dump();
	}
}

#pragma once

#include <json.hpp>

class RestServer;

class MessageAgentBase
{
public:
	MessageAgentBase(RestServer* server);
	virtual ~MessageAgentBase();

protected:
	RestServer* _server;

public:
	virtual void SetupMessageHandler() = 0;
};

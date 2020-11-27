#pragma once

#include <enum.h>
#include <json.hpp>
#include <MyLogger.h>

class JsonSerializationObject
{
	virtual bool FromJson(const nlohmann::json& r) = 0;
	virtual bool ToJson(nlohmann::json& w) = 0;
};
#pragma once

#include "Global.h"

#include <json.hpp>
#include <list>

class JsonHelper
{
public:
	static bool GetBoolField(const nlohmann::json& obj, const char* fieldName, bool& fieldValue);
	static bool GetFloatField(const nlohmann::json& obj, const char* fieldName, float& fieldValue);
	static bool GetInt64Field(const nlohmann::json& obj, const char* fieldName, int64_t& fieldValue);
	static bool GetLongField(const nlohmann::json& obj, const char* fieldName, long &fieldValue);
	static bool GetIntField(const nlohmann::json& obj, const char* fieldName, int32_t& fieldValue, bool must = true);
	static bool GetInt64ArrayField(const nlohmann::json& obj, const char* fieldName, std::list<int64_t>& fieldValue);
	static bool GetIntArrayField(const nlohmann::json& obj, const char* fieldName, std::list<int32_t>& fieldValue);
	static bool GetStringField(const nlohmann::json& obj, const char* fieldName, std::string& fieldValue);
	static bool GetStringArrayField(const nlohmann::json& obj, const char* fieldName, std::list<std::string>& fieldValue);
	static bool GetArrayField(const nlohmann::json& obj, const char* fieldName, nlohmann::json& fieldObj, bool must = true);
	static bool GetObjectField(const nlohmann::json& obj, const char* fieldName, nlohmann::json& fieldObj);
	static bool GetField(const nlohmann::json& obj, const char* fieldName, nlohmann::json& fieldObj, bool must = true);
};

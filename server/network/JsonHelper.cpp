#include "JsonHelper.h"

#include "MyLogger.h"

using namespace std;
using json = nlohmann::json;

bool JsonHelper::GetBoolField(const json& obj, const char* fieldName, bool& fieldValue)
{
	json fieldObj;
	if (!GetField(obj, fieldName, fieldObj))
		return false;

	if (!fieldObj.is_boolean())
	{
		LOG_ERROR("[{0:s}] isn't Boolean in {1:s}", fieldName, obj.dump());
		return false;
	}

	fieldValue = fieldObj.get<bool>();

	return true;
}

bool JsonHelper::GetFloatField(const json& obj, const char* fieldName, float& fieldValue)
{
	json fieldObj;
	if (!GetField(obj, fieldName, fieldObj))
		return false;

	if (!fieldObj.is_number())
	{
		LOG_ERROR("[{0:s}] isn't Number in {1:s}", fieldName, obj.dump());
		return false;
	}

	fieldValue = fieldObj.get<float>();

	return true;
}

bool JsonHelper::GetInt64Field(const json& obj, const char* fieldName, int64_t& fieldValue)
{
	json fieldObj;
	if (!GetField(obj, fieldName, fieldObj))
		return false;

	if (!fieldObj.is_number_integer())
	{
		LOG_ERROR("[{0:s}] isn't Interger64 in {1:s}", fieldName, obj.dump());
		return false;
	}

	fieldValue = fieldObj.get<int64_t>();

	return true;
}

bool JsonHelper::GetLongField(const json& obj, const char* fieldName, long& fieldValue)
{
	json fieldObj;
	if (!GetField(obj, fieldName, fieldObj))
		return false;

	if (!fieldObj.is_number_integer())
	{
		LOG_ERROR("[{0:s}] isn't Long in {1:s}", fieldName, obj.dump());
		return false;
	}

	fieldValue = fieldObj.get<long>();

	return true;
}

bool JsonHelper::GetIntField(const json& obj, const char* fieldName, int32_t& fieldValue, bool must)
{
	json fieldObj;
	if (!GetField(obj, fieldName, fieldObj, must))
		return false;

	if (!fieldObj.is_number_integer())
	{
		LOG_ERROR("[{0:s}] isn't Integer in {1:s}", fieldName, obj.dump());
		return false;
	}

	fieldValue = fieldObj.get<int32_t>();

	return true;
}

bool JsonHelper::GetInt64ArrayField(const json& obj, const char* fieldName, list<int64_t>& fieldValue)
{
	json fieldObj;
	if (!GetArrayField(obj, fieldName, fieldObj))
		return false;

	fieldValue = fieldObj.get<list<int64_t>>();

	return true;
}

bool JsonHelper::GetIntArrayField(const json& obj, const char* fieldName, list<int32_t>& fieldValue)
{
	json fieldObj;
	if (!GetArrayField(obj, fieldName, fieldObj))
		return false;

	fieldValue = fieldObj.get<list<int32_t>>();

	return true;
}

bool JsonHelper::GetStringField(const json& obj, const char* fieldName, string& fieldValue)
{
	json fieldObj;
	if (!GetField(obj, fieldName, fieldObj))
		return false;

	if (!fieldObj.is_string())
	{
		LOG_ERROR("[{0:s}] isn't String in {1:s}", fieldName, obj.dump());
		return false;
	}

	fieldValue = fieldObj.get<string>();

	return true;
}

bool JsonHelper::GetStringArrayField(const json& obj, const char* fieldName, list<string>& fieldValue)
{
	json fieldObj;
	if (!GetArrayField(obj, fieldName, fieldObj))
		return false;

	fieldValue = fieldObj.get<list<string>>();

	return true;
}

bool JsonHelper::GetArrayField(const json& obj, const char* fieldName, json& fieldObj, bool must)
{
	if (!GetField(obj, fieldName, fieldObj, must))
		return false;

	if (!fieldObj.is_array())
	{
		LOG_ERROR("[{0:s}] isn't Array in {1:s}", fieldName, obj.dump());
		return false;
	}

	return true;
}

bool JsonHelper::GetObjectField(const json& obj, const char* fieldName, json& fieldObj)
{
	if (!GetField(obj, fieldName, fieldObj))
		return false;

	if (!fieldObj.is_object())
	{
		LOG_ERROR("[{0:s}] isn't Object in {1:s}", fieldName, obj.dump());
		return false;
	}

	return true;
}

bool JsonHelper::GetField(const json& obj, const char* fieldName, json& fieldObj, bool must)
{
	if (obj.find(fieldName) == obj.end())
	{
		if(must)
			LOG_ERROR("can't find [{:s}] in ", obj.dump());
		return false;
	}

	fieldObj = obj[fieldName];

	return true;
}

#include "TableBase.h"

#include "MyLogger.h"

using namespace std;
using namespace tinyxml2;

TableBase::TableBase()
{
}

TableBase::~TableBase()
{
}

bool TableBase::LoadXml(const std::string& name)
{
	string fileName = name + ".xml";
	string filePath = "Table/" + fileName;

	_doc.LoadFile(filePath.c_str());
	if (_doc.Error())
	{
		LOG_ERROR("{0:s} load error: {1:s}", fileName, _doc.ErrorName());
		return false;
	}

	return true;
}
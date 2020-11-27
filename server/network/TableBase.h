#pragma once

#include <string>
#include <tinyxml2.h>

class TableBase
{
public:
	TableBase();
	virtual ~TableBase();

protected:
	tinyxml2::XMLDocument _doc;

public:
	bool LoadXml(const std::string& name);
};

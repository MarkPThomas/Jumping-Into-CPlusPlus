#pragma once
#include <string>

class StringConvertable
{
public:
	virtual ~StringConvertable();
	virtual std::string toString() = 0;
};

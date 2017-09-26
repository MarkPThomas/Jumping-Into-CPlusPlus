#pragma once
#include<string>

class Comparator
{
public:
	virtual ~Comparator();
	virtual int compare(const std::string& lhs, const std::string& rhs) = 0;
};

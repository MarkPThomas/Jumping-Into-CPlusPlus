#pragma once
#include <string>
#include "Comparator.h"

class ReverseSort : public Comparator
{
public:
	virtual int compare(const std::string& lhs, const std::string& rhs);
};
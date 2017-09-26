#pragma once
#include <string>
#include "Comparator.h"

class CaseInsensitiveSort : public Comparator
{
public:
	virtual int compare(const std::string& lhs, const std::string& rhs);
};

#pragma once
#include "StringConvertable.h"

class Bar : public StringConvertable
{
public:
	std::string toString() override;
};

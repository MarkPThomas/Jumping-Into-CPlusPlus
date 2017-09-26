#pragma once
#include "StringConvertable.h"

class Foo : public StringConvertable
{
public:
	std::string toString() override;
};


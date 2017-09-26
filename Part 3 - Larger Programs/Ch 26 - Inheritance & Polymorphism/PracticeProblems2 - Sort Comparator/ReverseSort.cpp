#include <string>
#include "ReverseSort.h"

int ReverseSort::compare(const std::string& lhs, const std::string& rhs)
{
	if (lhs > rhs)
	{
		return 1;
	}
	if (lhs < rhs)
	{
		return -1;
	}
	return 0;
}
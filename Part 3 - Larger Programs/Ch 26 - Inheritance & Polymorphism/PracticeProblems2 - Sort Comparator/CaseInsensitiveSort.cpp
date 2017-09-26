#include <string>
#include "CaseInsensitiveSort.h"

int CaseInsensitiveSort::compare(const std::string& lhs, const std::string& rhs)
{
	int lhsLength = lhs.length();
	int rhsLength = rhs.length();
	
	// Simple check for empty strings
	if (lhsLength != 0 && rhsLength == 0)
	{
		return 1;
	}
	if (lhsLength == 0 && rhsLength != 0)
	{
		return -1;
	}
	if (lhsLength == 0 && rhsLength == 0)
	{
		return 0;
	}

	// Check if strings are identical across the shortest character count
	int minLength;
	lhsLength < rhsLength ? minLength = lhsLength : minLength = rhsLength;
	for (int i = 0; i < minLength; i++)
	{
		if (tolower(lhs[i]) != tolower(rhs[i]))
		{
			if (tolower(lhs[i]) > tolower(rhs[i]))
			{
				return 1;
			}
			return -1;
		}
	}

	// If strings are identical across the shortest string length, then the strings can be compared by length
	if (lhsLength == rhsLength)
	{
		return 0;
	}
	if (lhsLength > rhsLength)
	{
		return 1;
	}
	return -1;
}
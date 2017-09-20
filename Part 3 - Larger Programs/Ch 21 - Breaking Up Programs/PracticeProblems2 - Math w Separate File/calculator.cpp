#include <cmath>
#include "calculator.h"

int add(int lhs, int rhs)
{
	return (lhs + rhs);
}

int subtract(int lhs, int rhs)
{
	return (lhs - rhs);
}

int multiply(int lhs, int rhs)
{
	return (lhs * rhs);
}

int divide(int lhs, int rhs)
{
	if (rhs == 0)
	{
		return INFINITY;
	}
	return (lhs / rhs);
}
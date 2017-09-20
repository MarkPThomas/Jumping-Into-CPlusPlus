#include <iostream>

using namespace std;

int main()
{
	int factorial = 1;
	for (int i = 0; i < 10; i++)
	{
		factorial *= i;
	}

	int sum = 0;
	for (int i = 0; i < 10; i++)
	{
		sum += i;
	}

	// Factorial w/o 2
	int factorialWithoutTwo = 1;
	for (int i = 0; i < 10; i++)
	{
		if (i == 2)
		{
			continue;
		}
		factorialWithoutTwo *= i;
	}

	// Sum w/o 2
	int sumWithoutTwo = 0;
	for (int i = 0; i < 10; i++) 
	{
		if (i = 2) // This is the bug. i is assigned 2, so the for loop never finishes.
		//if (i == 2) // This fixes the bug.
		{
			continue;
		}
		sumWithoutTwo += i;
	}
}
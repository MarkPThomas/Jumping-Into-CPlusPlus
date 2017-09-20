#include <iostream>

using namespace std;

int exponent(int base, int exp)
{
	//int runningValue; // This is the bug. The variable needs to be initialized.
	int runningValue = 1;
	for (int i = 0; i < exp; i++)
	{
		runningValue *= base;
	}
	return base;
}

int main()
{
	int base;
	int exp;

	cout << "Enter a base value: ";
	cin >> base;
	cout << "Enter a exponent: ";
	cin >> exp;
	cout << base << "^" << exp << " = " << exponent(exp, base) << endl;
}
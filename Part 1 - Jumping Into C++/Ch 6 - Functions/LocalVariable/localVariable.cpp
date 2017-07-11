#include <iostream>

using namespace std;

void changeArgument (int x)
{
	x += 5;
}

int divide(int numerator, int denominator)
{
	if (0 == denominator)
	{
		int result = 0;
			return result;
	}
	int result = numerator / denominator;
	return result;
}

int main()
{
	int y = 4;
	changeArgument(y); // y will be unharmed by the function call

	cout << y << "\n"; // still prints 4

	cout << divide(4, 2) << "\n";

	cout << divide(4, 0) << "\n";
}
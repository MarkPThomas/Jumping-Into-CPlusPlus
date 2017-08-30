#include<iostream>

using namespace std;

int pow(int x, int y)
{
	// x^1 = x
	// x^2 = x*x
	// x^3 = x*x*x
	
	// Base Case
	if (y == 1)
	{
		return x;
	}

	return x * pow(x, y - 1);
}

int main()
{
	cout << "Let's calculate x^y\n";

	int x = 0;
	do
	{
		cout << "Enter a positive value for x: ";
		cin >> x;
	} while (x < 1);

	int y = 0;
	do
	{
		cout << "Enter a positive value for y: ";
		cin >> y;
	} while (y < 1);
	
	int result = pow(x, y);
	cout << "x^y = " << x << "^" << y << " = " << result << '\n';
}
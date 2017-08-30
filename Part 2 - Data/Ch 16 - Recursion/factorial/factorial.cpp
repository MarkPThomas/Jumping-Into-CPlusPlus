#include<iostream>

using namespace std;

int factorialRecursion(int x)
{
	if (x == 1)
	{
		cout << "1";
		return 1;
	}
	int result = x * factorialRecursion(x - 1);
	cout << "*" << x;
	return result;
}

int factorialLoop(int x)
{
	int current = x;
	cout << x;
	while (x > 1)
	{
		x--;
		current *= x;
		cout << "*" << x;
	}
	
	return current;
}

int main()
{
	cout << "Please specify a number to use in the factorial x*(x-1)*(x-2)...*1\n";
	int x;
	cin >> x;
	cout << '\n';

	cout << "Result of the recursive function is as follows... ";
	int recursiveResult = factorialRecursion(x);
	cout << " = " << recursiveResult << '\n';

	cout << "Result of the loop function is as follows... ";
	int loopResult = factorialLoop(x);
	cout << " = " << loopResult << '\n';
}



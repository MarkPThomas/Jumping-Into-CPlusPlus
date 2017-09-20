#include <iostream>

using namespace std;

int fibonacci (int n)
{
	//if (n == 0) // This is the bug. fibonacci(n-2) will overshoot the base case of n==0 that ends the recursion.
	// This fixes the bug:
	if (n <= 1)
	{
		//return 1; // Another bug. 
		return n;
	}
	return fibonacci(n - 1) + fibonacci(n - 2); // This triggers the bug.
}

int main()
{
	int n;
	cout << "Enter the number to compute fibonacci for: " << endl;
	cin >> n;
	cout << fibonacci(n) << endl;
}
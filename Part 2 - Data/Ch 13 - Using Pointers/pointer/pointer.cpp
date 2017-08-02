#include <iostream>

using namespace std;

int main()
{
	// A normal integer
	int x; 
	
	// A pointer to an integer
	int *p_int;

	// Read it, "assign the address of x to p_int"
	p_int = &x;

	cout << "Please enter a number: ";
	
	// Put a value in x, we could also use *p_int here
	cin >> x;

	// Note the use of the * to get the value
	cout << *p_int << '\n';

	*p_int = 10;

	// Outputs 10 again!
	cout << x;
}
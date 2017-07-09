#include <iostream>

using namespace std;

int main()
{
	int firstArgument;
	int secondArgument;
	cout << "Enter first argument: ";
	cin >> firstArgument;
	cout << "Enter second argument: ";
	cin >> secondArgument;
	
	cout << firstArgument << " * " << secondArgument
		<< " = " << firstArgument * secondArgument
		<< endl;

	cin.ignore();
	cin.get();
}
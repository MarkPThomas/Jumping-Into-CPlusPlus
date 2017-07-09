#include <iostream>
 
using namespace std;

int main()
{
	double x;
	cout << "Enter a number: ";
	cin >> x;
	if (x < 10)
	{
		cout << "You entered a value less than 10" << '\n';
	}
	else if (x > 10)
	{
		cout << "You entered a number greater than 10" << '\n';
	}
	else
	{
		cout << "You entered 10" << '\n';
	}
}
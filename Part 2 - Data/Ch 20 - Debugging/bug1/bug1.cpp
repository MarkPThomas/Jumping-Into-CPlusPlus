#include <iostream>

using namespace std;

double computeInterest(double baseValue, double rate, int years)
{
	//double finalMultiplier; // This is the bug. It is not initialized.
	double finalMultiplier = 1; // This fixes the bug.
	for (int i = 0; i < years; i++)
	{
		finalMultiplier *= (1 + rate);
	}
	return baseValue*finalMultiplier;
}

int main()
{
	double baseValue;
	double rate;
	int  years;
	cout << "Enter a base value: ";
	cin >> baseValue;
	cout << "Enter an interest rate: ";
	cin >> rate;
	cout << "Enter the number of years to compound: ";
	cin >> years;
	cout << "After " << years << " you will have " << computeInterest(baseValue, rate, years) << " money" << endl;
}
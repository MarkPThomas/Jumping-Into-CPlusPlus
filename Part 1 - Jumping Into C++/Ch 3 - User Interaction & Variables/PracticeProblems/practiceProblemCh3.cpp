#include <iostream>
#include <string>

using namespace std;

int main()
{
	string name;
	cout << "Please enter your name: " << endl;
	// This gets the entire line. Otherwise, if spaces are used, only the first word is stored.
	getline(cin, name, '\n'); 
	cout << "Your name is: " << name << "\n";

	double number1 = 0;
	double number2 = 0;
	cout << "Please enter two numbers to add together. \nFirst Number: ";
	cin >> number1;
	cout << "\nSecond Number:";
	cin >> number2;

	double result = number1 + number2;
	cout << "The result is:\n" << number1 << " + " << number2 << " = " << result << "\n";

	cout << "Please enter two numbers to divide together. \nNumerator: ";
	cin >> number1;
	cout << "\nDenominator:" << endl;
	cin >> number2;
	result = number1 / number2;
	cout << "The result is:\n" << number1 << " / " << number2 << " = " << result << endl;
}
#include <iostream>
#include <string>
#include "calculator.h"

using namespace std;

int add(int lhs, int rhs)
{
	return (lhs + rhs);
}

int subtract(int lhs, int rhs)
{
	return (lhs - rhs);
}

int multiply(int lhs, int rhs)
{
	return (lhs * rhs);
}

int divide(int lhs, int rhs)
{
	if (rhs == 0)
	{
		return INFINITY;
	}
	return (lhs / rhs);
}

int main()
{
	while (true)
	{
		int choice = 0;
		bool isValidChoice = false;
		while (!isValidChoice)
		{
			cout << "Choose from the following operations:\n";
			cout << "0. Exit\n";
			cout << "1. Add\n";
			cout << "2. Subtract\n";
			cout << "3. Multiply\n";
			cout << "4. Divide\n";
			cin >> choice;

			if (choice == 0)
			{
				return 0;
			}
			isValidChoice = (0 <= choice && choice <= 4);
			if (!isValidChoice)
			{
				cout << "Please enter a valid number.\n";
			}
			cout << '\n';
		}
		
		int lhs = 0;
		cout << "Left-hand side value: ";
		cin >> lhs;
		cout << '\n';

		int rhs = 0;
		cout << "Right-hand side value: ";
		cin >> rhs;
		cout << '\n';

		int result;
		string operatorSymbol;
		switch (choice)
		{
		case 1:
			result = add(lhs, rhs);
			operatorSymbol = "+";
			break;
		case 2:
			result = subtract(lhs, rhs);
			operatorSymbol = "-";
			break;
		case 3:
			result = multiply(lhs, rhs);
			operatorSymbol = "*";
			break;
		case 4:
			result = divide(lhs, rhs);
			operatorSymbol = "/";
			break;
		default:
			result = add(lhs, rhs);
			operatorSymbol = "+";
			break;
		}
		cout << lhs << " " << operatorSymbol << " " << rhs << " = " << result << "\n\n";
	}
}
#include <iostream>
#include <string>

using namespace std;

template <typename  Type>
class Calc
{
public:
	Calc();
	Type multiply(Type x, Type y);
	Type add(Type x, Type y);
};

template <typename Type> 
Calc<Type>::Calc()
{}

template <typename Type>
Type Calc<Type>::multiply(Type x, Type y)
{
	return x * y;
}

template <typename Type>
Type Calc<Type>::add(Type x, Type y)
{
	return x + y;
}

int main()
{
	cout << "Sample run of a template calculation class...\n";

	int xint = 4;
	int yint = 6;
	Calc<int> calcInt;
	cout << "Integer type:\n";
	cout << "x + y = " << xint << " + " << yint << " = " << calcInt.add(xint, yint) << '\n';
	cout << "x * y = " << xint << " * " << yint << " = " << calcInt.multiply(xint, yint) << '\n';
	cout << endl;

	double xdbl = 4.32;
	double ydbl = 6.99;
	Calc<double> calcDbl;
	cout << "Double type:\n";
	cout << "x + y = " << xdbl << " + " << ydbl << " = " << calcDbl.add(xdbl, ydbl) << '\n';
	cout << "x * y = " << xdbl << " * " << ydbl << " = " << calcDbl.multiply(xdbl, ydbl) << '\n';
	cout << endl;

	string xstr = "4";
	string ystr = "6";
	Calc<string> calcStr;
	cout << "String type (expected to work incorrectly for addition fail for multiplication):\n";
	cout << "x + y = " << xstr << " + " << ystr << " = " << calcStr.add(xstr, ystr) << '\n';
	//cout << "x * y = " << xstr << " * " << ystr << " = " << calcStr.multiply(xstr, ystr) << '\n';
	cout << endl;
}
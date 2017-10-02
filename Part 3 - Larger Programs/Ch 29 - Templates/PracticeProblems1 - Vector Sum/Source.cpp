#include <iostream>
#include <string>
#include <vector>
#include "vectorSum.hxx"

using namespace std;

int main()
{
	cout << "Sample run of a template calculation class...\n";

	vector<int> vectorInt;
	vectorInt.push_back(5);
	vectorInt.push_back(4);
	vectorInt.push_back(3);
	vectorInt.push_back(2);
	vectorInt.push_back(1);
	vectorInt.push_back(0);
	VectorSum<int> calcInt;
	cout << "Integer type:\n";
	cout << "Sum(vector) = " << calcInt.sum(vectorInt) << '\n'; // Should sum to 15
	cout << endl;

	vector<double> vectorDbl;
	vectorDbl.push_back(5.5);
	vectorDbl.push_back(4.4);
	vectorDbl.push_back(3.3);
	vectorDbl.push_back(2.2);
	vectorDbl.push_back(1.1);
	vectorDbl.push_back(0);
	VectorSum<double> calcDbl;
	cout << "Double type:\n";
	cout << "Sum(vector) = " << calcDbl.sum(vectorDbl) << '\n'; // Should sum to 16.5
	cout << endl;

	//vector<string> vectorStr;
	//vectorStr.push_back("5.5");
	//vectorStr.push_back("4.4");
	//vectorStr.push_back("3.3");
	//vectorStr.push_back("2.2");
	//vectorStr.push_back("1.1");
	//vectorStr.push_back("0");
	//vectorStr.push_back("Foo");
	//vectorStr.push_back("Bar");
	//VectorSum<string> calcStr;
	//cout << "String type (expected to work incorrectly for addition fail for multiplication):\n";
	//cout << "Sum(vector) = " << calcStr.sum(vectorStr) << '\n'; // Should fail due to invalid null reference for string characters
	//cout << endl;
}
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename Type>
bool isInVector(const Type& searchItem, const vector<Type>& vectorToSearch)
{
	for (typename vector<Type>::const_iterator itr = vectorToSearch.begin(), end = vectorToSearch.end();
		itr != end;
		++itr)
	{
		if (searchItem == *itr)
		{
			return true;
		};
	}
	return false;
}

string isInVectorToString(int result)
{
	string stringResult;
	result == 0 ? stringResult = "False" : stringResult = "True";
	return stringResult;
}

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
	cout << "Integer type:\n";
	for (int i = 0; i < 6; i++)
	{
		cout << vectorInt[i] << '\n';
	}
	int searchTrueInt = 2;
	int seachFalseInt = 6;
	cout << "Is " << searchTrueInt << " in the list? Answer: " << isInVectorToString(isInVector(searchTrueInt, vectorInt)) <<'\n';
	cout << "Is " << seachFalseInt << " in the list? Answer: " << isInVectorToString(isInVector(seachFalseInt, vectorInt)) << '\n';
	cout << endl;

	vector<double> vectorDbl;
	vectorDbl.push_back(5.5);
	vectorDbl.push_back(4.4);
	vectorDbl.push_back(3.3);
	vectorDbl.push_back(2.2);
	vectorDbl.push_back(1.1);
	vectorDbl.push_back(0);
	cout << "Double type:\n";
	for (int i = 0; i < 6; i++)
	{
		cout << vectorDbl[i] << '\n';
	}
	double searchTrueDbl = 3.3;
	double seachFalseDbl = 5.6;
	cout << "Is " << searchTrueDbl << " in the list? Answer: " << isInVectorToString(isInVector(searchTrueDbl, vectorDbl)) << '\n'; // This may still return false due to floating point issues.
	cout << "Is " << seachFalseDbl << " in the list? Answer: " << isInVectorToString(isInVector(seachFalseDbl, vectorDbl)) << '\n';
	cout << endl;

	vector<string> vectorStr;
	vectorStr.push_back("5.5");
	vectorStr.push_back("4.4");
	vectorStr.push_back("3.3");
	vectorStr.push_back("2.2");
	vectorStr.push_back("1.1");
	vectorStr.push_back("0");
	vectorStr.push_back("Foo");
	vectorStr.push_back("Bar");
	cout << "String type:\n";
	for (int i = 0; i < 6; i++)
	{
		cout << vectorStr[i] << '\n';
	}
	string searchTrueStr = "Foo";
	string seachFalseStr = "Moo";
	cout << "Is " << searchTrueStr << " in the list? Answer: " << isInVectorToString(isInVector(searchTrueStr, vectorStr)) << '\n';
	cout << "Is " << seachFalseStr << " in the list? Answer: " << isInVectorToString(isInVector(seachFalseStr, vectorStr)) << '\n';
	cout << endl;
}
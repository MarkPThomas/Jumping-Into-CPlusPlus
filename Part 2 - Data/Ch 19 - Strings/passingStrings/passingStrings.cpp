#include <iostream>
#include <string>

using namespace std;

void printStringNonConstVal(string str)
{
	cout << str;
}

void printStringNonConstRef(string& str)
{
	cout << str; 
	str = "abc"; // Legal! Changes string.
}

void printStringConstRef(const string& str)
{
	cout << str; // Legal, doesn't modify str.
	//str = "abc"; // Not legal!
}

void printStringConstPtr(const string* str)
{
	if (str == nullptr) // OK, memory str points to is not modified.
	{
		return;
	}

	cout << *str;	// OK memory access is OK.
	//*str = 20;		// NOT OK, memory str points to is modified.
	str = nullptr;	// OK, not modifying memory, just the pointer itself.
}

void main()
{
	string stringToShow = "there is one x in this string";
	printStringNonConstVal(stringToShow);
	cout << '\n';

	printStringNonConstRef(stringToShow);
	cout << '\n';

	// Note that the non constant variable can be passed in as a constant parameter.
	printStringConstRef(stringToShow);
	cout << '\n';
	// This conversion cannot be be done in the opposite way (e.g. const value passed in to nonconst parameter)
	const string constStringToShow = "this string shall never change!";
	printStringConstRef(constStringToShow);
	cout << '\n';
	//printStringNonConstRef(constStringToShow);
	//cout << '\n';

	printStringConstPtr(&constStringToShow);
	cout << '\n';
}
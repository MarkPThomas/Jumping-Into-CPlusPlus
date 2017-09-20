#include <iostream>
#include <string>

using namespace std;

int main()
{
	string myString = "abcdefghijklmnop";
	string firstTenOfAlphabet = myString.substr(0, 10);
	cout << "The first ten letters of the alphabet are " << firstTenOfAlphabet;
}
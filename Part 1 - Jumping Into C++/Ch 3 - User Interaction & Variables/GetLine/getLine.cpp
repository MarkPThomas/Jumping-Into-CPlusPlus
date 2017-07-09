#include <iostream>
#include <string>

using namespace std;

int main()
{
	string userInput;
	cout << "Write anything, and it will be returned: " << endl;
	getline(cin, userInput, '\n');
	cout << userInput << endl;

	cout << "Write anything with a comma and only the first part of the sentence will be returned: " << endl;
	getline(cin, userInput, ',');
	cout << userInput << endl;

	cin.ignore();
	cin.get();
}
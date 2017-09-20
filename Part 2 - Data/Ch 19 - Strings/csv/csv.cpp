#include <iostream>
#include <string>

using namespace std;

int main()
{
	while(1)
	{
		cout << "Please enter {first name}, {last name}, {player class}...\n";
		string firstName;
		getline(cin, firstName, ',');

		if (firstName.size() == 0)
		{
			break;
		}
		
		string lastName;
		getline(cin, lastName, ',');

		string playerClass;
		getline(cin, playerClass, '\n');
		cout << firstName << " " << lastName << " is a " << playerClass << endl;
		cout << '\n';
	}
}
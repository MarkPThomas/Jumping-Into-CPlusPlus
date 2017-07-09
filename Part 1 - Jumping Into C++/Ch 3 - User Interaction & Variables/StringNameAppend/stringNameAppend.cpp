#include <iostream>
#include <string>

using namespace std;

int main()
{
	string userFirstName;
	string userLastName;

	cout << "Please enter your first name: ";
	cin >> userFirstName;
	cout << "Please enter your last name: ";
	cin >> userLastName;
	
	string userFullName = userFirstName + " " + userLastName;
	
	cout << "Your name is: " << userFullName << "\n";

	cin.ignore();
	cin.get();
}
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string password;

	cout << "Enter your password: " << "\n";
	getline(cin, password, '\n');
	if (password == "guest")
	{
		cout << "Access allowed" << "\n";
	}
	else
	{
		cout << "Bad password. Denied access!" << "\n";
		// returning is a convenient way to stop the program
		return 0;
	}
	// Continue onward!
}
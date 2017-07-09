#include <iostream>
#include <string>

using namespace std;

int main()
{
	string password;
	while (1) // same as while (true)
	{
		cout << "Please enter your password: ";
		cin >> password;
		if (password == "foobar")
		{
			cout << "Entry granted..." << "\n";
			break; // breaks out of the loop at this location
		}

		int i = 0;
		cout << "Bad password! Counting up to your doom!" << "\n";
		while (true)
		{
			i++;
			if ( i == 10)
			{
				continue; // Skips the current iteration
			}
			cout << i << "\n";
			if (i > 15)
			{
				break; // breaks out of inner loop
			}
		}
	}
}
#include <iostream>

using namespace std;

int main()
{
	int thisIsANumber;

	cout << "Please enter a number: ";
	cin >> thisIsANumber;
	cout << "You entered: " << thisIsANumber << "\n";

	// When pressing enter for console applications, cin.get() does not keep the console open.
	// Instead, use below, which ignores the 'enter' command.
	// Alternatively, in Visual Studio press Alt-F5, although you will not have debugging information.
	cin.ignore();
	cin.get();
}
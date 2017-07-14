#include <iostream>
#include <string>

using namespace std;

int main()
{
	string username1;
	int username1Age;

	cout << "Please enter a user and their age.\n";
	cout << "Username: \n";
	cin >> username1;
	cout << "Age: \n";
	cin >> username1Age;

	string username2;
	int username2Age;
	
	cout << "Please enter another user and their age.\n";
	cout << "Username: \n";
	cin >> username2;
	cout << "Age: \n";
	cin >> username2Age;

	if ((username1Age) > 100 && (username2Age > 100))
	{
		cout << "Wow! Both users are really old!" << "\n";
	}
	else if (username1Age > username2Age)
	{
		cout << username1 << " is older than " << username2 << "\n";
	}
	else if (username2Age > username1Age)
	{
		cout << username2 << " is older than " << username1 << "\n";
	}
	else
	{
		cout << username1 << " is the same age as " << username2 << "\n";
	}
}
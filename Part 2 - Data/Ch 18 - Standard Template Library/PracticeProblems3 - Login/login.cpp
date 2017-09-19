#include<iostream>
#include<string>
#include<map>

using namespace std;

void registerUser(map<string, string>& users);
string createName(map<string, string>& users);
bool validateName(string name, map<string, string>& users);
string createPassword();
bool validatePassword(string password);

void login(map<string, string>& users);
string validLoginName(map<string, string>& users);
bool validateLoginName(string name, map<string, string>& users);
string validLoginPassword(string name, map<string, string>& users);
bool validateLoginPassword(string name, string password, map<string, string>& users);
void loginAction(string name, map<string, string>& users);
void changePassword(string name, map<string, string>& users);

bool nameExists(string name, map<string, string>& users);
void printUsers(map<string, string>& users);

int main()
{
	int choice = 0;
	bool exitProgram = false;
	map<string, string> users;

	while (!exitProgram)
	{
		cout << "Please select from the following options:\n";
		cout << "0. Exit\n";
		cout << "1. Register User\n";
		if (users.size() > 0)
		{
			cout << "2. Login\n";
		}
		cout << '\n';
		cin >> choice;

		switch (choice)
		{
		case 0:
			exitProgram = true;
			break;
		case 1:
			registerUser(users);
			printUsers(users);
			break;
		case 2:
			login(users);
			printUsers(users);
			break;
		default:
			exitProgram = true;
			break;
		}
		cout << '\n';
	}
	users.clear();
}

void registerUser(map<string, string>& users)
{
	string name = createName(users);
	if (name == "0") { return; }
	string password = createPassword();
	if (password == "0") { return; }
	users[name] = password;
}

string createName(map<string, string>& users)
{
	string name = "";
	bool validName = false;

	while (!validName)
	{
		name = "";
		cout << "Please create a login name: \n";
		cout << "(0 to exit)\n";
		cin >> name;
		if (name == "0") { break; }
		validName = validateName(name, users);
		if (!validName)
		{
			cout << "The name provided already exist...\n\n";
		}
	}
	cout << '\n';
	return name;
}

bool validateName(string name, map<string, string>& users)
{
	if (name == "") { return false; }
	return !nameExists(name, users);
}

string createPassword()
{
	string password = "";
	bool validPassword = false;

	while (!validPassword)
	{
		password = "";
		cout << "Please create a password as any contiguous set of numbers and characters at least 6 characters long: \n";
		cout << "(0 to exit)\n";
		cin >> password;
		if (password == "0") { break; }
		validPassword = validatePassword(password);
		if (!validPassword)
		{
			cout << "The password provided is not valid...\n\n";
		}
	}
	cout << '\n';
	return password;
}

bool validatePassword(string password)
{
	return (password.length() >= 6);
}

void login(map<string, string>& users)
{
	bool logout = false;

	while (!logout)
	{
		string name = validLoginName(users);
		if (name == "0") { return; }
		string password = validLoginPassword(name, users);
		if (password == "0") { return; }
		loginAction(name, users);
		logout = true;
	}
}

string validLoginName(map<string, string>& users)
{
	string name = "";
	bool validName = false;

	while (!validName)
	{
		name = "";
		cout << "Please provide a login name: \n";
		cout << "(0 to exit)\n";
		cin >> name;
		if (name == "0") { break; }
		validName = validateLoginName(name, users);
		if (!validName)
		{
			cout << "The name provided does not exist...\n\n";
		}
	}
	cout << '\n';
	return name;
}

bool validateLoginName(string name, map<string, string>& users)
{
	return nameExists(name, users);
}

string validLoginPassword(string name, map<string, string>& users)
{
	string password = "";
	bool validPassword = false;

	while (!validPassword)
	{
		password = "";
		cout << "Please provide a password: \n";
		cout << "(0 to exit)\n";
		cin >> password;
		if (password == "0") { break; }
		validPassword = validateLoginPassword(name, password, users);
		if (!validPassword)
		{
			cout << "The password provided is incorrect...\n\n";
		}
	}
	cout << '\n';
	return password;
}

bool validateLoginPassword(string name, string password, map<string, string>& users)
{
	string actualPassword = users[name];
	return (password == actualPassword);
}


void loginAction(string name, map<string, string>& users)
{
	int choice = 0;
	bool logout = false;

	while (!logout)
	{
		cout << "Please select from the following options:\n";
		cout << "1. Change password for " << name << "\n";
		cout << "2. Log Out\n";
		cout << '\n';
		cin >> choice;

		switch (choice)
		{
		case 0:
			logout = true;
			break;
		case 1:
			changePassword(name, users);
			break;
		case 2:
			logout = true;
			break;
		default:
			logout = true;
			break;
		}
		cout << '\n';
	}
}

void changePassword(string name, map<string, string>& users)
{
	string password = "";
	bool validPassword = false;

	while (!validPassword)
	{
		password = "";
		cout << "Please create a new password as any contiguous set of numbers and characters at least 6 characters long: \n";
		cout << "(0 to exit)\n";
		cin >> password;
		if (password == "0") { break; }
		validPassword = validatePassword(password);
		if (validPassword)
		{
			users[name] = password;
		}
	}
}

bool nameExists(string name, map<string, string>& users)
{
	return (users.find(name) != users.end());
}

void printUsers(map<string, string>& users)
{
	cout << '\n';
	cout << "Users\n";
	cout << "===================\n";
	for (map<string, string>::iterator itr = users.begin(), end = users.end(); itr != end; ++itr)
	{
		cout << itr->first << ": " << itr->second << "\n";
	}
	cout << "===================\n";
	cout << '\n';
}
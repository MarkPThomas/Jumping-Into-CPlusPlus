#include <iostream>
#include <map>
#include <string>

using namespace std;

map<string, string>& createEntry(map<string, string>& myMap);
map<string, string>& modifyEntry(map<string, string>& myMap);
map<string, string>& removeEntry(map<string, string>& myMap);
void displayEntry(map<string, string>& myMap);
void printAddressBook(map<string, string>& myMap);
void getMapKeysUnsorted(map<string, string>& myMap, string nodeKeys[], int currentIndex = 0);
const int maxNumberOfNodes = 100;

int main()
{
	map<string, string> myMap;

	bool exitProgram = false;
	int choice = 0;

	while (!exitProgram)
	{
		choice = 0;
		int numberOfNodes = myMap.size();
		cout << "Please choose from the following options:\n";
		cout << "0. Exit\n";
		cout << "1. Create entries\n";
		if (numberOfNodes > 0)
		{
			cout << "2. Add/Change e-mail (using name)\n";
			cout << "3. Remove e-mail (using name)\n";
			cout << "4. Display email (using name)\n";
		}
		cin >> choice;
		cout << '\n';

		switch (choice)
		{
		case 0:
			exitProgram = true;
			break;
		case 1:
			myMap = createEntry(myMap);
			printAddressBook(myMap);
			break;
		case 2:
			myMap = modifyEntry(myMap);
			printAddressBook(myMap);
			break;
		case 3:
			myMap = removeEntry(myMap);
			printAddressBook(myMap);
			break;
		case 4:
			displayEntry(myMap);
			break;
		default:
			exitProgram = true;
			break;
		}
	}

	myMap.clear();
}

void printAddressBook(map<string, string>& myMap)
{
	int numberOfNodes = myMap.size();
	if (numberOfNodes == 0)
	{
		return;
	}

	string mapKeys[maxNumberOfNodes];
	getMapKeysUnsorted(myMap, mapKeys);

	// Print nodes in order
	cout << "Address Book:\n";
	cout << "===========\n";
	string priorName = "";
	for (int i = 0; i < numberOfNodes; i++)
	{
		// Set current name to prior name, or first name if this is the first iteration.
		string currentName;
		priorName == "" ? currentName = mapKeys[0] : currentName = priorName;

		// Get next name in order
		for (int index = 0; index < numberOfNodes; index++)
		{
			if ((mapKeys[index] > priorName) &&
				((currentName == priorName) ||
				(mapKeys[index] < currentName)))
			{
				currentName = mapKeys[index];
			}
		}

		cout << "Name:  " << currentName << '\n';
		cout << "Email: " << myMap[ currentName ] << "\n\n";

		priorName = currentName;
	}
	cout << "===========\n\n";
}

void getMapKeysUnsorted(map<string, string>& myMap, string nodeKeys[], int currentIndex)
{
	for (map<string, string>::iterator itr = myMap.begin(), end = myMap.end(); itr != end; ++itr) {
		nodeKeys[currentIndex] = itr->first;
		currentIndex++;
	}
}


void displayEntry(map<string, string>& map)
{
	string name = "";
	string email = "";
	cin.ignore();

	do
	{
		name = "";
		cout << "Please enter a name from the address book to display:\n";
		getline(cin, name, '\n');
		if (name == "") { break; }

		// Check that the name does not exist
		if (map.find(name) == map.end())
		{
			cout << "That entry does not exist. \n";
			cout << "Please enter an existing name to display.\n";
			continue;
		}

		cout << '\n';
		cout << name << ": " << map[name] << "\n\n";
	} while (name != "");
}

map<string, string>& createEntry(map<string, string>& map)
{
	string name = "";
	string email = "";
	cin.ignore();

	do
	{
		name = "";

		cout << "Please enter a name for the address book:\n";
		getline(cin, name, '\n');
		if (name == "") { break; }

		// Check that the name does not exist
		if (map.find(name) != map.end())
		{
			cout << "That entry already exists. \n";
			cout << "Please enter a unique name to add, or choose to modify an existing entry.\n";
			continue;
		}
		cout << "Please enter an email address for the name:\n";
		getline(cin, email, '\n');

		map[name] = email;
		cout << "\n\n";
	} while (name != "");

	return map;
}

map<string, string>& modifyEntry(map<string, string>& map)
{
	string name = "";
	string email = "";
	cin.ignore();

	do
	{
		name = "";
		cout << "Please enter a name for the email to modify:\n";
		getline(cin, name, '\n');
		if (name == "") { break; }

		// Check that the name exists
		if (map.find(name) == map.end())
		{
			cout << "That entry does not exist. \n";
			cout << "Please enter an existing name to modify.\n";
			continue;
		}

		cout << "Please enter a new email address for the name:\n";
		getline(cin, email, '\n');

		map[name] = email;
		cout << "\n\n";
	} while (name != "");

	return map;
}

map<string, string>& removeEntry(map<string, string>& map)
{
	string name = "";
	string email = "";
	cin.ignore();

	do
	{
		name = "";
		cout << "Please enter a name to remove:\n";
		getline(cin, name, '\n');
		if (name == "") { break; }

		// Check that the name exists
		if (map.find(name) == map.end())
		{
			cout << "That entry does not exist. \n";
			cout << "Please enter an existing name to remove.\n";
			continue;
		}

		map.erase(name);
		cout << name << " has been removed from the address book.\n\n";
	} while (name != "");

	return map;
}




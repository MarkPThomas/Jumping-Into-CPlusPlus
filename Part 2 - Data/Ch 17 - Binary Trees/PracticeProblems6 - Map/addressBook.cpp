#include <iostream>
#include <string>
#include "map.h"

using namespace std;

node* createEntry(node* map);
node* modifyEntry(node* map);
node* removeEntry(node* map);
void displayEntry(node* map);
void printAddressBook(node* map);
int getMapKeysUnsorted(node* map, string nodeKeys[], int currentIndex = 0);
int countNodes(node* map, int count);

const int maxNumberOfNodes = 100;

int main()
{
	node* map = nullptr;

	bool exitProgram = false;
	int choice = 0;

	while(!exitProgram)
	{
		choice = 0;
		int numberOfNodes = countNodes(map, 0);
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
			map = createEntry(map);
			printAddressBook(map);
			break;
		case 2:
			map = modifyEntry(map);
			printAddressBook(map);
			break;
		case 3:
			map = removeEntry(map);
			printAddressBook(map);
			break;
		case 4: 
			displayEntry(map);
			break;
		default:
			exitProgram = true;
			break;
		}
	}
	
	destroyMap(map);
}

void printAddressBook(node* map)
{
	int numberOfNodes = countNodes(map, 0);
	if (numberOfNodes == 0)
	{
		return;
	}

	string mapKeys[maxNumberOfNodes];
	getMapKeysUnsorted(map, mapKeys);

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
		cout << "Email: " << getValue(map, currentName) << "\n\n";

		priorName = currentName;
	}
	cout << "===========\n\n";
}

int getMapKeysUnsorted(node* map, string nodeKeys[], int currentIndex)
{
	if (!map)
	{
		return currentIndex;
	}

	currentIndex = getMapKeysUnsorted(map->left, nodeKeys, currentIndex);
	currentIndex = getMapKeysUnsorted(map->right, nodeKeys, currentIndex);

	nodeKeys[currentIndex] = map->key;
	return currentIndex + 1;
}

int countNodes(node* map, int count)
{
	if (!map)
	{
		return count;
	}

	count = countNodes(map->left, count);
	count = countNodes(map->right, count);

	return count + 1;
}



void displayEntry(node* map)
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
		if (!search(map, name))
		{
			cout << "That entry does not exist. \n";
			cout << "Please enter an existing name to display.\n";
			continue;
		}
		
		cout << '\n';
		cout << name << ": " << getValue(map, name) << "\n\n";
	} while (name != "");
}

node* createEntry(node* map)
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
		if (search(map, name))
		{
			cout << "That entry already exists. \n";
			cout << "Please enter a unique name to add, or choose to modify an existing entry.\n";
			continue;
		}
		cout << "Please enter an email address for the name:\n";
		getline(cin, email, '\n');

		map = insert(map, name, email);
		cout << "\n\n";
	} while (name != "");

	return map;
}

node* modifyEntry(node* map)
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
		if (!search(map, name))
		{
			cout << "That entry does not exist. \n";
			cout << "Please enter an existing name to modify.\n";
			continue;
		}

		cout << "Please enter a new email address for the name:\n";
		getline(cin, email, '\n');

		map = insert(map, name, email); 
		cout << "\n\n";
	} while (name != "");

	return map;
}

node* removeEntry(node* map)
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
		if (!search(map, name))
		{
			cout << "That entry does not exist. \n";
			cout << "Please enter an existing name to remove.\n";
			continue;
		}

		map = remove(map, name);
		cout << name << " has been removed from the address book.\n\n";
	} while (name != "");

	return map;
}




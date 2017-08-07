// User has list of friends
// # of days ago last spoke to each friend

#include <iostream>
#include <string>

using namespace std;

void updateArray(string** p_p_array, int size, string name, int daySinceLastSpoken);
string** addToArray(string** p_p_array, int* size, string name, int daySinceLastSpoken);
void disposeArray2D(string** p_p_array2D, int arrayWidth);
string** arraySortedByName(string** p_p_array, int size);
string** arraySortedByDate(string** p_p_array, int size);
bool nameExistsInArray(string** p_p_array, int size, string name);
string lookUpName(string** p_p_array, int size, string daysSinceLastSpoken);
string getName();
int getDaysSinceLastSpoken();
int getDaysSinceLastSpoken(int lastDaysSinceLastSpoken);
int lookUpDaysSinceLastSpoken(string** p_p_array, int size, string name);

string getNameToUpdate(string** p_p_array, int size);
void printFriends(string** p_p_array, int size);
void printFriendsByName(string** p_p_array, int size);
void printFriendsByDate(string** p_p_array, int size);

// Insertion Sort
int findSmallestRemainingElement(string* array, int size, int index);
void swap(string* array, int firstIndex, int secondIndex);
void sort(string* array, int size);

bool isNumber(string value);
bool isCharacterNumeric(char value);

int main()
{
	int arrayWidth = 2;
	int arrayLength = 0;
	string** p_p_array = new string*[arrayWidth];

	int option = 0;
	string name;
	int daysSinceLastSpoken;
	do
	{
		cout << "Please select an option:\n";
		cout << "(1) Add new friend\n";
		if(arrayLength > 0)
		{
			cout << "(2) Update friend\n";
			cout << "(3) List friends by name\n";
			cout << "(4) List friends by most recently spoken with\n";
		}
		cout << "(0) Exit\n";
		cin >> option;
		cout << '\n';
		switch (option)
		{
		case 0:
			break;
		case 1:
			name = getName();
			daysSinceLastSpoken = getDaysSinceLastSpoken();
			p_p_array = addToArray(p_p_array, &arrayLength, name, daysSinceLastSpoken);
			cout << '\n';
			break;
		case 2:
			name = getNameToUpdate(p_p_array, arrayLength);
			daysSinceLastSpoken = lookUpDaysSinceLastSpoken(p_p_array, arrayLength, name);
			daysSinceLastSpoken = getDaysSinceLastSpoken(daysSinceLastSpoken);
			updateArray(p_p_array, arrayLength, name, daysSinceLastSpoken);
			cout << '\n';
			break;
		case 3:
			printFriendsByName(p_p_array, arrayLength);
			cout << '\n';
			break;
		case 4:
			printFriendsByDate(p_p_array, arrayLength);
			cout << '\n';
			break;
		default:
			break;
		}
	}
	while (option != 0);

	disposeArray2D(p_p_array, 2);
}

string getName()
{
	string name;
	cout << "Friend name: ";
	cin.ignore();
	cin.clear();
	getline(cin, name, '\n');
	cout << '\n';
	return name;
}

int getDaysSinceLastSpoken()
{
	int daysSinceLastSpokenInput = 0;
	do
	{
		cout << "Number of days ago you last spoke with them: ";
		cin >> daysSinceLastSpokenInput;

		if (daysSinceLastSpokenInput < 0)
		{
			cout << "Please enter a value >= 0\n";
		}
	} while (daysSinceLastSpokenInput < 0);
	cout << '\n';
	return daysSinceLastSpokenInput;
}

int getDaysSinceLastSpoken(int lastDaysSinceLastSpoken)
{
	int daysSinceLastSpokenInput = 0;
	do
	{
		cout << "Number of days ago you last spoke with them: ";
		cin >> daysSinceLastSpokenInput;

		if (daysSinceLastSpokenInput <0)
		{
			cout << "Please enter a value >= 0\n\n";
		}
		if (daysSinceLastSpokenInput > lastDaysSinceLastSpoken)
		{
			cout << "You last spoke with your friend " << lastDaysSinceLastSpoken << " days ago.\n";
			cout << "You must enter a number less than or equal to this.\n\n";
		}
	} while ((daysSinceLastSpokenInput < 0) || (daysSinceLastSpokenInput > lastDaysSinceLastSpoken));
	cout << '\n';
	return daysSinceLastSpokenInput;
}

int lookUpDaysSinceLastSpoken(string** p_p_array, int size, string name)
{
	for (int i = 0; i < size; i++)
	{
		if (p_p_array[0][i] == name) { return stoi(p_p_array[1][i]); }
	}
	return -1;
}

string lookUpName(string** p_p_array, int size, string daysSinceLastSpoken)
{
	for (int i = 0; i < size; i++)
	{
		if (p_p_array[1][i] == daysSinceLastSpoken) { return p_p_array[0][i]; }
	}
	return "";
}

string getNameToUpdate(string** p_p_array, int size)
{
	string name;
	do
	{
		printFriendsByName(p_p_array, size);
		cout << '\n';
		cout << "Please enter an existing name to update: ";
		cin >> name;
		cout << '\n';
	}
	while (!nameExistsInArray(p_p_array, size, name));
	return name;
}

bool nameExistsInArray(string** p_p_array, int size, string name)
{
	for (int i = 0; i < size; i++)
	{
		if (p_p_array[0][i] == name) { return true; }
	}
	return false;
}

void updateArray(string** p_p_array, int size, string name, int daySinceLastSpoken)
{
	for (size_t i = 0; i < size; i++)
	{
		if (p_p_array[0][i] == name)
		{
			p_p_array[1][i] = to_string(daySinceLastSpoken);
			return;
		}
	}
}


string** addToArray(string** p_p_array, int* size, string name, int daySinceLastSpoken)
{
	// Create a new array of the new size
	string** p_p_newvalues = new string*[2];
	for (int i = 0; i < 2; i++)
	{
		p_p_newvalues[i] = new string[*size + 1];
	}

	// Copy all current array values over if there are any to copy
	if (*size > 0)
	{
		for (int i = 0; i < *size; i++)
		{
			p_p_newvalues[0][i] = p_p_array[0][i];
			p_p_newvalues[1][i] = p_p_array[1][i];
		}
	}
	
	// Add new values
	p_p_newvalues[0][*size] = name;
	p_p_newvalues[1][*size] = to_string(daySinceLastSpoken); // daySinceLastSpokenString;

	if (*size > 0)
	{
		// Remove the current array to free up memory (i.e. avoid a memory leak).
		disposeArray2D(p_p_array, 2);
	}

	*size += 1; // Note: Do NOT use ++ operator on int* size, as that will increment the memory address rather than the value, regardless of *size++ vs. size++;
	return p_p_newvalues;
}


void disposeArray2D(string** p_p_array2D, int arrayWidth)
{
	for (size_t j = 0; j < arrayWidth; j++)
	{
		delete[] p_p_array2D[j];
	}

	delete[] p_p_array2D;
}


string** arraySortedByName(string** p_p_array, int size)
{
	// Create array to sort, and sort it
	string* names = new string[size];
	for (int i = 0; i < size; i++)
	{
		names[i] = p_p_array[0][i];
	}
	sort(names, size);

	// Create new array and fill it based on the sorted array
	string** p_p_newArray = new string*[2];
	for (int i = 0; i < 2; i++)
	{
		p_p_newArray[i] = new string[size];
	}

	for (int i = 0; i < size; i++)
	{
		// Add next entry based on sorting array
		string name = names[i];
		int daysSinceLastSpoken = lookUpDaysSinceLastSpoken(p_p_array, size, name);
		for (int j = 0; j < size; j++)
		{
			if (p_p_array[0][j] == name)
			{
				p_p_newArray[0][i] = name;
				p_p_newArray[1][i] = to_string(daysSinceLastSpoken);
				break;
			}
		}
	}

	return p_p_newArray;
}

string** arraySortedByDate(string** p_p_array, int size)
{
	// Create array to sort, and sort it
	string* dates = new string[size];
	for (int i = 0; i < size; i++)
	{
		dates[i] = p_p_array[1][i];
	}
	sort(dates, size);

	// Create new array and fill it based on the sorted array
	string** p_p_newArray = new string*[2];
	for (int i = 0; i < 2; i++)
	{
		p_p_newArray[i] = new string[size];
	}

	for (int i = 0; i < size; i++)
	{
		// Add next entry based on sorting array
		string date = dates[i];
		string name = lookUpName(p_p_array, size, date);
		for (int j = 0; j < size; j++)
		{
			if (p_p_array[1][j] == date)
			{
				p_p_newArray[0][i] = name;
				p_p_newArray[1][i] = date;
				break;
			}
		}
	}

	return p_p_newArray;
}

void printFriendsByName(string** p_p_array, int size)
{
	string** sortedArray = arraySortedByName(p_p_array, size);
	printFriends(sortedArray, size);
	disposeArray2D(sortedArray, 2);
}

void printFriendsByDate(string** p_p_array, int size)
{
	string** sortedArray = arraySortedByDate(p_p_array, size);
	printFriends(sortedArray, size);
	disposeArray2D(sortedArray, 2);
}

void printFriends(string** p_p_array, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << p_p_array[0][i] << ": " << p_p_array[1][i] << " days since last spoken\n";
	}
}


// Insertion Sort
void sort(string* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		int index = findSmallestRemainingElement(array, size, i);
		swap(array, i, index);
	}
}


int findSmallestRemainingElement(string* array, int size, int index)
{
	int indexOfSmallestValue = index;
	for (int i = index + 1; i < size; i++)
	{
		// A special check of converted numbers is needed as "100" < "3" when comparing strings.
		if (isNumber(array[i]))
		{
			int arrayCurrent = stoi(array[i]);
			int arraySmallest = stoi(array[indexOfSmallestValue]);
			if (arrayCurrent < arraySmallest)
			{
				indexOfSmallestValue = i;
			}
		}
		else
		{
			if (array[i] < array[indexOfSmallestValue])
			{
				indexOfSmallestValue = i;
			}
		}
	}
	return indexOfSmallestValue;
}


void swap(string* array, int firstIndex, int secondIndex)
{
	string temp = array[firstIndex];
	array[firstIndex] = array[secondIndex];
	array[secondIndex] = temp;
}

bool isNumber(string value)
{
	for (int i = 0; i < value.length(); i++)
	{
		if (!isCharacterNumeric(value[i]))
		{
			return false;
		}
	}
	return true;
}


bool isCharacterNumeric(char value)
{
	return (value == '0' || 
			value == '1' ||
			value == '2' ||
			value == '3' ||
			value == '4' ||
			value == '5' ||
			value == '6' ||
			value == '7' ||
			value == '8' ||
			value == '9');
}
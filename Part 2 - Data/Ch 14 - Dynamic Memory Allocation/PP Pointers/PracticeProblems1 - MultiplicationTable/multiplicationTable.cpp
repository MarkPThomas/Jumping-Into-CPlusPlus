#include <iostream>
#include <string>

using namespace std;

void printBoard(int tableSize, int** table, int maxEntrySize);
string numberWithPadding(int number, int maxSize);
int numberOfPaddingItems(int number, int maxSize);

int main()
{
	int tableSize = 3;

	cout << "Please specify the size of the multiplication table (Default is 3x3): ";
	cin >> tableSize;

	int** p_p_table;
	// Notice that the assignment is to an int*, since we are allocating an array of pointers.
	p_p_table = new int*[tableSize];

	// Now make each pointer store the address of an array of integers.
	for (size_t i = 0; i < tableSize; i++)
	{
		p_p_table[i] = new int[tableSize];
	}

	// Now we can use the allocated memory just like a 2-dimensional array.
	// For example, we can initialize the entire board with a pair of for loops:
	for (size_t i = 0; i < tableSize; i++)
	{
		for (size_t j = 0; j < tableSize; j++)
		{
			p_p_table[i][j] = i * j;
		}
	}
	int maxEntrySize = (tableSize - 1)*(tableSize - 1);
	printBoard(tableSize, p_p_table, maxEntrySize);

	// To free the memory, we go in exactly the opposite order that we used to initialize it:
	// (1) Free each row.
	// (2) Free the pointer that holds the rows.
	for (size_t i = 0; i < tableSize; i++)
	{
		delete[] p_p_table[i];
	}
	delete[] p_p_table;
}

string numberWithPadding(int number, int maxSize)
{
	string numberAsString = to_string(number);
	string zeros;
	int paddingCount = numberOfPaddingItems(number, maxSize);
	if (paddingCount > 0)
	{
		for (int i = 0; i < paddingCount; i++)
		{
			zeros += '0';
		}
		numberAsString = zeros + numberAsString;
	}
	return numberAsString;
}

int numberOfPaddingItems(int number, int maxSize)
{
	string numberAsString = to_string(number);
	string maxSizeAsString = to_string(maxSize);

	string zeros;
	return (maxSizeAsString.length() - numberAsString.length());
}

void printBoard(int tableSize, int** p_p_table, int maxEntrySize)
{
	string horizontalBar = " _";
	for (size_t i = 0; i < tableSize; i++)
	{
		horizontalBar += "__";
		int paddingCount = numberOfPaddingItems(1, maxEntrySize);
		if (paddingCount > 0)
		{
			for (int i = 0; i < paddingCount; i++)
			{
				horizontalBar += "_";
			}
		}
	}

	for (size_t i = 0; i <= tableSize; i++)
	{
		if (i == 0)
		{
			for (size_t j = 0; j <= tableSize; j++)
			{
				if (j == 0)
				{
					cout << " ";
				}
				else
				{
					cout << " " << numberWithPadding(j - 1, maxEntrySize);
				}
			}
			cout << "\n";
		}
		else
		{
			cout << horizontalBar << "\n";
			for (size_t j = 0; j <= tableSize; j++)
			{
				if (j == 0)
				{
					cout << i - 1;
				}
				else
				{
					string value = numberWithPadding(p_p_table[i - 1][j - 1], maxEntrySize);
					cout << "|" << value;
				}
			}
			cout << "|\n";
		}
	}
	cout << horizontalBar << "\n\n";
}




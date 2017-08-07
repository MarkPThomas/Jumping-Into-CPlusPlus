#include <iostream>
#include <string>

using namespace std;

void printTable(int tableWidth, int tableLength, int tableRow, int*** table, int maxEntrySize);
string numberWithPadding(int number, int maxSize);
int numberOfPaddingItems(int number, int maxSize);
int** initializeTable2D(int tableWidth, int tableLength);
void disposeTable2D(int** p_p_table2D, int tableWidth);

int main()
{
	int tableLength = 3;
	int tableWidth = 3;
	int tableHeight = 3;

	cout << "Please specify the size of the multiplication table (Default is 3x3x3): \n";
	cout << "Table length:";
	cin >> tableLength;

	cout << "Table width:";
	cin >> tableWidth;

	cout << "Table height:";
	cin >> tableHeight;


	int*** p_p_table3D;
	// Notice that the assignment is to an int**, since we are allocating an array of pointers to an array of pointers.
	p_p_table3D = new int**[tableHeight];

	// Now make each pointer store the address of an array of pointers.
	for (size_t i = 0; i < tableHeight; i++)
	{
		p_p_table3D[i] = initializeTable2D(tableWidth, tableLength);
	}

	// Now we can use the allocated memory just like a 3-dimensional array.
	// For example, we can initialize the entire table with a triplet of for loops:
	for (size_t i = 0; i < tableHeight; i++)
	{
		for (size_t j = 0; j < tableWidth; j++)
		{
			for (size_t k = 0; k < tableLength; k++)
			{
				p_p_table3D[i][j][k] = i * j * k;
			}
		}
	}
	int maxEntrySize = (tableWidth - 1)*(tableLength - 1)*(tableHeight - 1);
	
	int displayPlane = 1;
	while (displayPlane != 0)
	{
		cout << "Please specify which 2D table plane to print from the 3D table of " << tableHeight << " layers. (0 Exits)\n";
		cout << "Current layer is: " << displayPlane << '\n';
		cin >> displayPlane;
		if (displayPlane == 0) {continue;}
		if (displayPlane < 0 || tableHeight < displayPlane)
		{
			cout << "You have selected a plane index that is out of bounds. Please try again.\n";
			continue;
		}
		printTable(tableWidth, tableLength, displayPlane, p_p_table3D, maxEntrySize);
	}

	// To free the memory, we go in exactly the opposite order that we used to initialize it:
	// (1) Free each row.
	// (2) Free the pointer that holds the rows.
	// (3) Free the pointer that holds the pointers.
	for (size_t i = 0; i < tableHeight; i++)
	{
		disposeTable2D(p_p_table3D[i], tableWidth);
	}
	delete[] p_p_table3D;
}

int** initializeTable2D(int tableWidth, int tableLength)
{
	int** p_p_table2D = new int*[tableWidth];
	for (size_t j = 0; j < tableWidth; j++)
	{
		p_p_table2D[j] = new int[tableLength];
	}
	return p_p_table2D;
}

void disposeTable2D(int** p_p_table2D, int tableWidth)
{
	for (size_t j = 0; j < tableWidth; j++)
	{
		delete[] p_p_table2D[j];
	}

	delete[] p_p_table2D;
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

void printTable(int tableWidth, int tableLength, int tableRow, int*** p_p_table, int maxEntrySize)
{
	string horizontalBar = " _";
	for (size_t i = 0; i < tableWidth; i++)
	{
		horizontalBar += "__";
		int paddingCount = numberOfPaddingItems(1, maxEntrySize);
		if (paddingCount > 0)
		{
			for (int i = 0; i < paddingCount; i++)
			{
				horizontalBar += "__";
			}
		}
	}

	for (size_t i = 0; i <= tableWidth; i++)
	{
		if (i == 0)
		{
			for (size_t j = 0; j <= tableLength; j++)
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
			for (size_t j = 0; j <= tableLength; j++)
			{
				if (j == 0)
				{
					cout << i - 1;
				}
				else
				{
					string value = numberWithPadding(p_p_table[tableRow - 1][i - 1][j - 1], maxEntrySize);
					cout << "|" << value;
				}
			}
			cout << "|\n";
		}
	}
	cout << horizontalBar << "\n\n";
}




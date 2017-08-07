#include <iostream>
#include <string>

using namespace std;

void printBoard(int boardSize, int** p_p_ticTacToe);
int sumMatrix(int values[][4], int numberOfRows);

int main()
{
	int boardSize = 3;
	
	cout << "Please specify the number of spaces for the square board (Default is 3x3): ";
	cin >> boardSize;

	int** p_p_ticTacToe;
	// Notice that the assignment is to an int*, since we are allocating an array of pointers.
	p_p_ticTacToe = new int*[boardSize];

	// Note that you cannot assign a 2-dimensional array to a pointer
	// Bad Code:
	// int x[8][8]
	// int **y = x;

	// Now make each pointer store the address of an array of integers.
	for (size_t i = 0; i < boardSize; i++)
	{
		p_p_ticTacToe[i] = new int[boardSize];
	}

	// Now we can use the allocated memory just like a 2-dimensional array.
	// For example, we can initialize the entire board with a pair of for loops:
	for (size_t i = 0; i < boardSize; i++)
	{
		for (size_t j = 0; j < boardSize; j++)
		{
			p_p_ticTacToe[i][j] = i+j;
		}
	}

	printBoard(boardSize, p_p_ticTacToe);

	// You cannot pass a pointer to a pointer into a function expecting a multi-dimensional array.
	// Bad Code:
	// int **x;
	// sumMatrix(x, 10); // allocate x to have 10 rows

	// To free the memory, we go in exactly the opposite order that we used to initialize it:
	// (1) Free each row.
	// (2) Free the pointer that holds the rows.
	for (size_t i = 0; i < boardSize; i++)
	{
		delete[] p_p_ticTacToe[i];
	}
	delete[] p_p_ticTacToe;
}


void printBoard(int boardSize, int** p_p_ticTacToe)
{
	string horizontalBar = " _";
	for (size_t i = 0; i < boardSize; i++)
	{
		horizontalBar += "__";
	}

	for (size_t i = 0; i <= boardSize; i++)
	{
		if (i == 0)
		{
			for (size_t j = 0; j <= boardSize; j++)
			{
				if (j == 0)
				{
					cout << " ";
				}
				else
				{
					cout << " " << j - 1;
				}
			}
			cout << "\n";
		}
		else
		{
			cout << horizontalBar << "\n";
			for (size_t j = 0; j <= boardSize; j++)
			{
				if (j == 0)
				{
					cout << i - 1;
				}
				else
				{
					int value = p_p_ticTacToe[i - 1][j - 1];
					cout << "|" << value;
				}
			}
			cout << "|\n";
		}
	}
	cout << horizontalBar << "\n\n";
}

int sumMatrix(int values[][4], int numberOfRows)
{
	int runningTotal = 0;
	for (size_t i = 0; i < numberOfRows; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			runningTotal += values[i][j];
		}
	}
	return runningTotal;
}


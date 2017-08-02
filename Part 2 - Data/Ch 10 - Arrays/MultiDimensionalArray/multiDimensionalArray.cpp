#include <iostream>

using namespace std;

int main()
{
	int array[8][8];	// Declares an array that looks like a chessboard

	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			// Set each element to a value
			array[i][j] = i * j;
		}
	}
	cout << "Multiplication table:\n";
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			cout << "[ " << i << " ][ " << j << " ] = ";
			cout << array[i][j] << " ";
			cout << "\n";
		}
	}
}
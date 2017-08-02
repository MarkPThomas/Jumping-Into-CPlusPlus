#include <iostream>

using namespace std;

// Note: You cannot determine the array size in C++ unless using a container class such as std::vector.
// Because of this, the array size must be passed in order to work on the function.

int sumArray(int values[], int size)
{
	int sum = 0;
	// This array stops when i == size. Why? THe last element is size - 1
	for (size_t i = 0; i < size; i++)
	{
		sum += values[i];
	}
	return sum;
}

int main()
{
	int const size = 10;

	int values[size];
	for (size_t i = 0; i < size; i++)
	{
		cout << "Enter value " << i << ": ";
		cin >> values[i];
	}
	cout << sumArray(values, size) << endl;
}
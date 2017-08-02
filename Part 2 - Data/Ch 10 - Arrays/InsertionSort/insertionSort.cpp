#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int findSmallestRemainingElement(int array[], int size, int index);
void swap(int array[], int firstIndex, int secondIndex);
void sort(int array[], int size);
void displayArray(int array[], int size);

int main()
{
	int const size = 10;
	int array[size];
	srand(time(nullptr));
	for (size_t i = 0; i < size; i++)
	{
		// Keep the numbers small so that they're easier to read
		array[i] = rand() % 100;
	}
	cout << "Original array: ";
	displayArray(array, size);
	cout << '\n';

	sort(array, size);

	cout << "Sorted array: ";
	displayArray(array, size);
	cout << '\n';
}


void sort(int array[], int size)
{
	for (size_t i = 0; i < size; i++)
	{
		int index = findSmallestRemainingElement(array, size, i);
		swap(array, i, index);
	}
}


int findSmallestRemainingElement(int array[], int size, int index)
{
	int indexOfSmallestValue = index;
	for (size_t i = index + 1; i < size; i++)
	{
		if (array[i] < array[indexOfSmallestValue])
		{
			indexOfSmallestValue = i;
		}
	}
	return indexOfSmallestValue;
}


void swap(int array[], int firstIndex, int secondIndex)
{
	int temp = array[firstIndex];
	array[firstIndex] = array[secondIndex];
	array[secondIndex] = temp;
}

/// <summary>
/// Small helper function to display the 'before' and 'after' arrays.
/// </summary>
/// <param name="array">The array.</param>
/// <param name="size">The size.</param>
void displayArray(int array[], int size)
{
	cout << "{";
	for (size_t i = 0; i < size; i++)
	{
		// You'll see this pattern a lot for nicely formatting lists
		// -- Check if we're past the first element, and if so, append a comma.
		if (i != 0)
		{
			cout << ", ";
		}
		cout << array[i];
	}
	cout << "}";
}
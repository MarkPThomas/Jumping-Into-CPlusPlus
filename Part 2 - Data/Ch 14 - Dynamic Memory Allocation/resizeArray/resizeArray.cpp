#include <iostream>

using namespace std;

int *growArray(int* p_values, int* size);
void printArray(int* p_values, int size, int elementsSet);

int main()
{
	int nextElement = 0;
	int size = 10;

	// Initially initialize array to 10 elements.
	int* p_values = new int[size];
	
	// Dynamically fill the array.
	int val;
	cout << "Please enter a number: ";
	cin >> val;
	while (val > 0)
	{
		if (size == nextElement + 1) // Array is full and needs to be resized before adding the next element.
		{
			// Now all we need to do is implement growArray.
			// Notice that we need to pass in size as a pointer since we need to keep track of the size of the array as it grows!
			p_values = growArray(p_values, & size);
		}
		p_values[nextElement] = val;
		nextElement++;
		cout << "Current array values are: " << endl;
		printArray(p_values, size, nextElement);
		cout << "Please enter a number (or 0 to exit):";
		cin >> val;
	}
}

void printArray(int* p_values, int size, int elementsSet)
{
	cout << "The total size of the array is: " << size << endl;
	cout << "Number of slots set so far: " << elementsSet << endl;
	cout << "Values in the array: " << endl;
	for (size_t i = 0; i < elementsSet; i++)
	{
		cout << "p_values[" << i << "] = " << p_values[i] << endl;
	}
	cout << "\n\n";
}

int* growArray(int* p_values, int* size)
{
	// Double the size of the array.
	// It is more efficient to always make the array larger than needed, than to increase the size of the array with each additional element.
	*size *= 2;	

	// Create a new array of the new size and copy all current array values over.
	int* p_newvalues = new int[*size];
	for (size_t i = 0; i < *size; i++)
	{
		p_newvalues[i] = p_values[i];
	}

	// Remove the current array to free up memory (i.e. avoid a memory leak).
	delete[] p_values;

	return p_newvalues;
}
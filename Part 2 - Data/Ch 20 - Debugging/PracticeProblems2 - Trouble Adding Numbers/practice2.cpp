#include <iostream>

using namespace std;

int sumValues(int* values, int n)
{
	//int sum; // This is one bug. This needs to be initialized.
	int sum = 0;
	//for (int i = 0; i <= n; i++) // This is another bug. Since 'i <= n', 'sum +=' bad memory again as it references a value beyond the max index of 'values'.
	// This fixes the bug
	for (int i = 0; i < n; i++)
	{
		sum += values[i];
	}
	return sum;
}

int main()
{
	int size;
	cout << "Enter a size: ";
	cin >> size;
	int* values = new int[size]; // This is another bug. The array is not initialized, so the indices contain random values.
	// This fixes the bug:
	for (int i = 0; i < size; i++)
	{
		values[i] = 0;
	}

	//int i; // This is another bug. It also needs to be initialized.
	int i = 0;
	while (i < size)
	{
		cout << "Enter a value to add: ";
		//cin >> values[++i]; // This is another bug. It increments before being used, so the first value is placed at index = 1.
		cin >> values[i++];
		cout << "Total sum is: " << sumValues(values, size) << endl;
	}
}
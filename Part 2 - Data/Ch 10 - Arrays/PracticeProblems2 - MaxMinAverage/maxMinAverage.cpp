#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int max(int array[], int size);
int min(int array[], int size);
double average(int array[], int size);

int main()
{
	int const size = 50;
	int array[size];
	srand(time(nullptr));
	for (size_t i = 0; i < size; i++)
	{
		// Keep the numbers small so that they're easier to read
		array[i] = rand() % 100;
	}
	
	int maxValue = max(array, size);
	int minValue = min(array, size);
	double averageValue = average(array, size);

	cout << "Max: " << maxValue << '\n';
	cout << "Min: " << minValue << '\n';
	cout << "Average: " << averageValue << '\n';

	cout << '\n' << "From the following: \n";
	for (size_t i = 0; i < size; i++)
	{
		cout << array[i] << '\n';
	}
}

int max(int array[], int size)
{
	int maxValue = array[0];
	for (size_t i = 0; i < size; i++)
	{
		if (array[i] > maxValue)
		{
			maxValue = array[i];
		}
	}
	return maxValue;
}

int min(int array[], int size)
{
	int minValue = array[0];
	for (size_t i = 0; i < size; i++)
	{
		if (array[i] < minValue)
		{
			minValue = array[i];
		}
	}
	return minValue;
}


double average(int array[], int size)
{
	double sum = 0;
	for (size_t i = 0; i < size; i++)
	{
		sum += array[i];
	}
	return sum/size;
}


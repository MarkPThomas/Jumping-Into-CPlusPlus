#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int randRange(int low, int high)
{
	// We get a random number, get it to be between 0 and the number of values in our range, 
	// then add the lowest possible value
	return rand() % (high - low + 1) + low;
}

int main()
{
	int sRandSeed = time(nullptr);
	srand(sRandSeed);

	int low = 4;
	int high = 10;
	int numberOfNumbers = 50;
	cout << "Random numbers bounded between " << low << " and " << high << '\n';
	for (size_t i = 0; i < numberOfNumbers; i++)
	{
		cout << randRange(low, high) << '\n';
	}
}

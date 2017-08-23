#include<iostream>

using namespace std;

int main()
{
	int const arraySize = 10;
	int votes[arraySize];

	// Make sure the election isn't rigged, by clearing out the array
	for (int i = 0; i < arraySize; i++)
	{
		votes[i] = 0;
	}

	int candidate;
	cout << "Vote for the candidate of your choice, using numbers:\n";
	cout << "0) Joe \n";
	cout << "1) Bob \n";
	cout << "2) Mary \n";
	cout << "3) Suzy \n";
	cout << "4) Margaret \n";
	cout << "5) Eleanor \n";
	cout << "6) Alex \n";
	cout << "7) Thomas \n";
	cout << "8) Andrew \n";
	cout << "9) Ilene \n";
	cin >> candidate;

	// Enter votes until the user exits by entering a non-candidate number
	while (0 <= candidate && candidate <= 9)
	{
		// Notice that we can't use a do-while loop because we need to check that the candidate is in the right range before updating the array.
		// A do-while loop would require reading in the candidate value, then checking it, then incrementing the vote
		votes[candidate]++;
		cout << "Please enter another vote: ";
		cin >> candidate;
	}

	// Display the votes
	for (int i = 0; i < arraySize; i++)
	{
		cout << votes[i] << '\n';
	}
}
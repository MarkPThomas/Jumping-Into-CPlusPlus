#include <iostream>

using namespace std;

int main()
{
	for (size_t i = 0; i < 9; i++)
	{
		// \t represents a tab character
		cout << '\t' << i;
	}
	cout << '\n';

	for (size_t i = 0; i < 9; ++i)
	{
		cout << i;
		for (size_t j = 0; j < 9; ++j)
		{
			cout << '\t' << i * j;
		}
		cout << '\n';
	}
}
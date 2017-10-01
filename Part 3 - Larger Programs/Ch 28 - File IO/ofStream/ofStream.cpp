#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	ofstream fileWriter("highScores.txt");
	if(!fileWriter.is_open())
	{
		cout << "Could not open file!" << '\n';
		return 0;
	}

	// Since we don't have any real scores, we'll output the numbers 10 to 1
	for (int i = 0; i < 10; i++)
	{
		fileWriter << 10 - i << '\n';
	}
}
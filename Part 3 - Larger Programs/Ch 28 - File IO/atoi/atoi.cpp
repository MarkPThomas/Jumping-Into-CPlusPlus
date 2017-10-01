#include <cstdlib>
#include <iostream>

using namespace std;

/// <summary>
/// Mains the specified argc.
/// </summary>
/// <param name="argc">The argument count.</param>
/// <param name="argv">The argument values.</param>
/// <returns>int.</returns>
int main(int argc, char* argv[])
{
	// argc should be 2 for correct execution:
	// 1. The program name
	// 2. The file name
	if (argc != 2)
	{
		// When printing out usage instruction, you can use argv[0] as the file name.
		cout << "Usage: " << argv[0] << " <filename>" << endl;
	}
	else
	{
		int val = atoi(argv[1]);
		cout << val * val;
	}
	cout << endl;
	return 0;
}
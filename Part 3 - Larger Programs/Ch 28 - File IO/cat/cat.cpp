#include <fstream>
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
		// We assume argv[1] is a filename to open.
		ifstream theFile(argv[1]);

		// Always check to see if file opening succeeded.
		if (!theFile.is_open())
		{
			cout << "Could not open file " << argv[1] << endl;
			return 1;
		}

		char x;
		// theFile.get(x) reads the next character from the file int x, 
		//   and returns false if the end of the file is hit or if an error occurs
		while (theFile.get(x))
		{
			cout << x;
		}
	}// theFile is closed implicitly here by its destructor.
  cout << endl;
}
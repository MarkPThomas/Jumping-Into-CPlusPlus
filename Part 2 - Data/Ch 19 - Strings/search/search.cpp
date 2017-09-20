#include <iostream>
#include <string>

using namespace std;

int main()
{
	string input;
	int i = 0;
	int catAppearances = 0;

	cout << "Please enter a line of text: ";
	getline(cin, input, '\n');

	// {variable}.find(string substring, int position) takes a substring position in the original string and finds the first occurrence of 
	//		the substring starting from the given index position.
	// {variable}.rfind(string substring, int position) takes a substring position in the original string and finds the first occurrence of 
	//		the substring starting from the given index position, working from the right end of the word to the left end.
	// {variable}.substr(int position, int length) creates a new string containing a slice of the string of a given length, beginning
	//		at a given position.
	for (i = input.find("cat", 0); // Starting value.
		 i != string::npos; // Terminating condion. string::npos is a special integer value that indicates that no substring was found.
		 i = input.find("cat", i)) // Current variable for the loop.
	{
		catAppearances++;

		// Move past last discovered instance to avoid finding the same string again
		i++;
	}
	cout << "The word cat appears " << catAppearances << " in the string " << '"' << input << '"';
}
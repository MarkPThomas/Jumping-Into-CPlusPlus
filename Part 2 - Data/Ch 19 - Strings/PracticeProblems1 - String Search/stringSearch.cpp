#include <iostream>
#include <string>

using namespace std;

int numberOfNeedlesInHaystack(const string& haystack, const string& needle);

int main()
{
	string needle;
	cout << "Please enter a line of text to find: ";
	getline(cin, needle, '\n');

	string haystack;
	cout << "Please enter a line of text to search for the number of occurrences: ";
	getline(cin, haystack, '\n');

	int needleAppearances = numberOfNeedlesInHaystack(needle, haystack);
	cout << "The word " << '"' << needle << '"' << " appears " << needleAppearances << " in the string " << '"' << haystack << '"';
}

int numberOfNeedlesInHaystack(const string& needle, const string& haystack)
{
	int i = 0;
	int needleAppearances = 0;
	for (i = haystack.find(needle, 0); // Starting value.
		i != string::npos; // Terminating condion. string::npos is a special integer value that indicates that no substring was found.
		i = haystack.find(needle, i)) // Current variable for the loop.
	{
		needleAppearances++;

		// Move past last discovered instance to avoid finding the same string again
		i++;
	}
	return needleAppearances;
}
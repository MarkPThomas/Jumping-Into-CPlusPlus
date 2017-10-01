#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void fileOpenStatus(ifstream& fileReader, string& fileName);

int main()
{ 
	cout << "Attempting to read invalid file...\n";
	string invalidFile = "myfile.txt";
	ifstream invalidFileReader(invalidFile);
	fileOpenStatus(invalidFileReader, invalidFile);
	cout << '\n';

	cout << "Attempting to read valid file...\n";
	string validFile = "myValidFile.txt";
	ifstream validFileReader(validFile);
	fileOpenStatus(validFileReader, validFile);
}

void fileOpenStatus(ifstream& fileReader, string& fileName)
{
	if (!fileReader.is_open())
	{
		cout << "Could not open file " << fileName << " !\n";
	}
	else
	{
		cout << "File " << fileName << " opened!\n";
	}
}
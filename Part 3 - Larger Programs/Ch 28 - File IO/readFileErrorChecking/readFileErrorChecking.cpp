#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void fileOpenStatus(ifstream& fileReader, string& fileName);
void fileReadStatus(ifstream& fileReader, int& number);

int main()
{
	cout << "Attempting to read invalid file...\n";
	string invalidFile = "myfile.txt";
	ifstream invalidFileReader(invalidFile);
	fileOpenStatus(invalidFileReader, invalidFile);
	cout << '\n';

	cout << "Attempting to read valid file with invalid data...\n";
	string validFile = "myValidFileInvalidData.txt";
	ifstream validFileReader(validFile);
	fileOpenStatus(validFileReader, validFile);
	int invalidNumber;
	// Here we're checking if reading in an integer succeeded or not:
	fileReadStatus(validFileReader, invalidNumber);
	cout << '\n';

	cout << "Attempting to read valid file with valid data...\n";
	string validFileValidData = "myValidFileValidData.txt";
	ifstream validFileReaderValidData(validFileValidData);
	fileOpenStatus(validFileReaderValidData, validFileValidData);
	int validNumber;
	// Here we're checking if reading in an integer succeeded or not:
	fileReadStatus(validFileReaderValidData, validNumber);
	cout << '\n';
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

void fileReadStatus(ifstream& fileReader, int& number)
{
	if (fileReader >> number)
	{
		cout << "First read value is: " << number << '\n';
	}
	else
	{
		cout << "First read value is incorrect: " << number << '\n';
	}
}
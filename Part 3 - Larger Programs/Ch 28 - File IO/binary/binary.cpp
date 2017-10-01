#include <fstream>
#include <string>
#include <iostream>

using namespace std;

struct PlayerRecord
{
	int age;
	int score;
	string name;
};

int main()
{
	// ===================== Writing to a file in binary =====================
	PlayerRecord rec;
	rec.age = 11;
	rec.score = 200;
	rec.name = "John";

	fstream aFile("records.bin",
		ios::trunc | ios::binary | ios::in | ios::out); // Opens the file in binary mode.

	// When writing in binary data, it is necessary to provide 1. the data as char*, and 2. the amounf of memory needed,
	// 1. reinterpret_cast<T> casts a type to an unrelated type. 
	//		It should only be used in cases such as this where we are converting data to char*, which is used to work with binary data.
	//		This results in an array of bytes by calling reinterpret_cast<char*>.
	//		If writing a constant variable, use reinterpret_cast<const char*>
	// 2. sizeOf() is used here to determine the amount of memory needed for the data.#
	//		If given a pointer, it will only return the size of the memory address!
	//		To work correctly with pointed, call it as sizeof(*variable).
	//		If the pointer points to an array, call it as sizeof(*variable)*length for *var = new int[length], for example.
	aFile.write(
		reinterpret_cast<char*>(&rec.age), 
		sizeof(rec.age)
	);

	aFile.write(
		reinterpret_cast<char*>(&rec.score),
		sizeof(rec.score)
	);

	// Since strings are references to characters, they must be treated differently.
	// If a string is recorded in the same was as the prior values, the pointer will also be recorded.
	// When read back in, this pointer will point to bad data.
	// c_str() gets a pointer to the string of characters in memory.
	// This ends with a character having the value 0.
	// This byte is called the null terminator and indicates the end of the string.
	// The string length is recorded as its own item, first, for later reading to allow proper sizing of the buffer.
	int len = rec.name.length(); 
	aFile.write(
		reinterpret_cast<char*>(&len),
		sizeof(len)
	);
	aFile.write(
		rec.name.c_str(),
		rec.name.length() + 1 // +1 for null terminator
	);


	// ===================== Reading from a file in binary =====================
	
	// Resetting file position
	aFile.seekg(0, ios::beg);
	
	PlayerRecord inRec;

	if (!aFile.read(
		reinterpret_cast<char*>(&inRec.age),
		sizeof(inRec.age)
			))
	{
		cout << "Error reading from file." << endl;
		return 1;
	}
	
	if (!aFile.read(
		reinterpret_cast<char*>(&inRec.score),
		sizeof(inRec.score)
			))
	{
		cout << "Error reading from file." << endl;
		return 1;
	}
	
	// Reading in a string
	int strLen;
	if (!aFile.read(
		reinterpret_cast<char*>(&strLen),
		sizeof(strLen)
			))
	{
		cout << "Error reading from file." << endl;
		return 1;
	}
	// Perform a sanity check to ensure we don't try to allocate too much memory!
	if (0 < strLen && strLen < 10000)
	{
		char* strBuff = new char[strLen + 1]; // +1 for null terminator
		if (!aFile.read(strBuff, strLen + 1)) // +1 for null terminator
		{
			delete[] strBuff;
			cout << "Error reading from file." << endl;
			return 1;
		}
		
		// Validate that the string is null-terminated
		if (strBuff[strLen] == 0)
		{
			inRec.name = string(strBuff);
		}
		delete[] strBuff;
	}
	cout << inRec.age << " " << inRec.score << " " << inRec.name << endl;
}
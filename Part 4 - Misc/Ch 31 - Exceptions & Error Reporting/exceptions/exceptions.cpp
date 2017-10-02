#include <iostream>
#include <string>
#include "fileNotFoundException.h"

using namespace std;

// Communicate what exceptions can be thrown by including a 'throw spec' in the function declarations & definitions..
void failableFunction() throw (FileNotFoundException);
void cannotFail() throw();

void failableFunction()
{
	throw FileNotFoundException(1, "File not found");
}

int callFailableFunction() throw (FileNotFoundException)
{
	const string val("abc");
	const int* valPointer = new int;
	// Call code that throws an exception
	try
	{
		failableFunction();
	}
	catch (...)
	{
		delete valPointer;
		// Notice the use of throw; to rethrow the exception.
		throw;
	}
	// Notice that we have to put delete here, too.
	// The catch block does not execute if there is no exception.
	// The only way to ensure that code is always run is to put it in the destructor of a local object.
	delete valPointer;
}

void cannotFail() throw()
{}

int main()
{
	try
	{
		callFailableFunction();
	}
	catch (const FileNotFoundException& e)
	{
		cout << "Exception thrown.\n";
		cout << "Error Code: " << e.getErrorCode() << endl;
		cout << "Error Message: " << e.getErrorReport() << endl;
	}
	catch (const Exception& e)
	{
		cout << "Superclass catching the exception\n";
	}
	catch (...) // catch-all
	{
		// Handle failure
		cout << "Catch-all handling the failure\n";
	}
}
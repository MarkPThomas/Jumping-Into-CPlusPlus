#include <iostream>

using namespace std;

// Just a small function to demonstrate scope.
int doStuff()
{
	return 2 + 3;
}

// Global variables can be initialized just like other variables.
int countOfFunctionCalls = 0;

void fun()
{
	// And the global variable is available here:
	countOfFunctionCalls++;
}

int main()
{
	fun();
	fun();
	fun();
	// And the global variable is also available here!
	cout << "Function was called " << countOfFunctionCalls << " times" << "\n";
}
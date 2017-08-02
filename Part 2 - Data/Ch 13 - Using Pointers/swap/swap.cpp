#include <iostream>

using namespace std;

// * used to declare a pointer
// * used to get/set value for an address

// Nothing used to declare a variable
// Nothing to get/set value stored in a variable
// Nothing to get/set the address stored in a pointer

// & used to get the address of a variable

void swap1(int left, int right)
{
	int temp = left;
	left = right;
	right = temp;
}

void swap2(int *p_left, int *p_right)
{
	int temp = *p_left;
	*p_left = *p_right;
	*p_right = temp;
}

void swap3(int &left, int &right)
{
	int temp = left;
	left = right;
	right = temp;
}

int main()
{
	int x = 1;
	int y = 2;

	cout << x << " " << y << '\n';

	cout << "Swapping with variables...\n";
	swap1(x, y);
	cout << x << " " << y << '\n';

	// Pointers can refer to NULL
	cout << "Swapping with pointers and addresses...\n";
	swap2(&x, &y);
	cout << x << " " << y << '\n';

	// References are a variable to another variable, sharing the same backing memory.
	// The actual memory of the variable holds a pointer to the memory of the referenced variable.
	// Declared with & and must always refer to valid memory & cannot be NULL - it must always be initialized.
	cout << "Swapping with references...\n";
	swap3(x, y);
	cout << x << " " << y << '\n';

	// Always intialize a pointer to null. 
	// This way te pointer can be checked as to whether or not it has been set to a usable memory address.
	// If a pointer is not null, you cannot check if it is pointing to valid memory
	int *p_int = nullptr;

	// Code that might or might not set p_int
	if (p_int != nullptr)
	{
		*p_int = 2;
	}
  
  // Code that will set p_int
	if (p_int == nullptr)
	{
		*p_int = 4;
	}
}
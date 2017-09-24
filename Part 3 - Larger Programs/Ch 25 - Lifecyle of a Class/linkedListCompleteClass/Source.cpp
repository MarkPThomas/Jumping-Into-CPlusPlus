#include <iostream>
#include "linkedList.h"

using namespace std;

void foo();

int main()
{
	// Destruction on delete
	LinkedList* list = new LinkedList();
	delete list; // ~LinkedList (the destructor) is called on list

	// Destruction when going out of scope
	bool loopControl = true;
	if (loopControl)
	{
		LinkedList list1;
		loopControl = false;
	} // List's destructor is called here as it falls out of scope

	foo();


	// Copy by assignment operator
	LinkedList list_one;
	LinkedList list_two;
	list_two = list_one;
	LinkedList list_three1 = list_two;


	// Copy by copy constructor
	LinkedList list_one1;
	LinkedList list_two1(list_one1);

	LinkedList list_one2;
	LinkedList list_two2 = list_one2; // This will automatically call the copy constructor as the assignment is made inline with the initialization.
}

void foo()
{
	LinkedList list;

	if(true)
	{
		return;
	}
} // List's destructor is called here as it falls out of scope
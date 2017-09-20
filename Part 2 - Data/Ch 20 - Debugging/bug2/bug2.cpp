#include <iostream>

using namespace std;

struct LinkedList
{
	int val;
	LinkedList *next;
};

void printList(const LinkedList *list)
{
	if (list)
	{
		cout << list->val;
		cout << "\n";
		printList(list->next);
	}
}

int main()
{
	LinkedList* list;
	list = new LinkedList;
	list->val = 10;
	list->next = new LinkedList;
	list->next->val = 11;
	// The bug is introduced here, as the 'next' value is never set to null, so it is pointing to an invalid memory location.
	// list->next->next = nullptr; // This fixes the bug.
	printList(list);

	return 0;
}
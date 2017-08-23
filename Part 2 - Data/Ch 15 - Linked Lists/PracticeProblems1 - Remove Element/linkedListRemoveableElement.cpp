#include <iostream>

using namespace std;

struct Item
{
	int ID;
	Item* nextItem;
	Item* previousItem;
};

Item* addToLinkedList(Item* p_list, int id);
Item* removeFromLinkedListWithTwoPointers(Item* p_item);
Item* removeFromLinkedListWithSinglePointer(Item* p_head, int target);

void printList(Item* p_list);

int main()
{
	Item* p_items = nullptr;
	Item* p_itemRemove = nullptr;
	Item* p_itemFirst = nullptr;
	Item* p_itemLast = nullptr;

	cout << "Create linked list of 10 items...\n";
	for (int i = 0; i < 10; i++)
	{
		p_items = addToLinkedList(p_items, i);
		if (i == 0)
		{
			p_itemFirst = p_items;
		}
		if (i == 5)
		{
			p_itemRemove = p_items;
		}
		if (i == 9)
		{
			p_itemLast = p_items;
		}
	}

	cout << "Remove ID 5 from the list w/ object & pointers...\n";
	p_items = removeFromLinkedListWithTwoPointers(p_itemRemove);
	printList(p_items);

	cout << "Remove ID 0 from the list (first element) w/ object & pointers...\n";
	p_items = removeFromLinkedListWithTwoPointers(p_itemFirst);
	printList(p_items);

	cout << "Remove ID 9 from the list (last element) w/ object & pointers...\n";
	p_items = removeFromLinkedListWithTwoPointers(p_itemLast);
	printList(p_items);


	cout << "Remove ID 2 from the list w/ target value...\n";
	p_items = removeFromLinkedListWithSinglePointer(p_items, 2);
	printList(p_items);

	cout << "Remove ID invalid from the list w/ target value...\n";
	p_items = removeFromLinkedListWithSinglePointer(p_items, 12);
	printList(p_items);

	cout << "Remove ID 1 from the list (first element) w/ target value...\n";
	p_items = removeFromLinkedListWithSinglePointer(p_items, 1);
	printList(p_items);

	cout << "Remove ID 8 from the list (last element) w/ target value...\n";
	p_items = removeFromLinkedListWithSinglePointer(p_items, 8);
	printList(p_items);

	delete p_items;
	delete p_itemFirst;
	delete p_itemLast;
	delete p_itemRemove;
}

Item* addToLinkedList(Item* p_list, int id)
{
	Item* p_item = new Item;
	p_item->ID = id;
	p_item->previousItem = nullptr;
	p_item->nextItem = p_list;
	if (p_list)
	{
		p_list->previousItem = p_item;
	}
	
	
	return p_item;
}

/// <summary>
/// Removes from linked list.
/// </summary>
/// <param name="p_item">The p item.</param>
Item* removeFromLinkedListWithTwoPointers(Item* p_item)
{
	Item* p_nextItem = p_item->nextItem;
	Item* p_previousItem = p_item->previousItem;

	if (!p_nextItem && !p_previousItem)
	{// Only element in the list
		p_item->nextItem = nullptr;
		p_item->previousItem = nullptr;
		return nullptr;
	}

	if (!p_nextItem && p_previousItem)
	{// First element in the list
		p_previousItem->nextItem = nullptr;

		// Reverse to the head to return
		while (p_previousItem->previousItem)
		{
			p_previousItem = p_previousItem->previousItem;
		}

		p_item->nextItem = nullptr;
		p_item->previousItem = nullptr;
		return p_previousItem;
	}
	

	if (!p_previousItem && p_nextItem)
	{ // Last element in the list
		p_nextItem->previousItem = nullptr;
	}
	else if (p_previousItem && p_nextItem)
	{ // Middle element in the list
		p_previousItem->nextItem = p_nextItem;
		p_nextItem->previousItem = p_previousItem;
	}
	
	// Rewind to the head to return
	while (p_nextItem->previousItem)
	{
		p_nextItem = p_nextItem->previousItem;
	}

	p_item->nextItem = nullptr;
	p_item->previousItem = nullptr;
	return p_nextItem;
}

Item* removeFromLinkedListWithSinglePointer(Item* p_head, int target)
{
	Item* p_current = p_head;
	Item* p_previous = p_current;

	while (p_current && p_current->ID != target)
	{
		p_previous = p_current;
		p_current = p_current->nextItem;
	}

	if (!p_current) { return p_head; } // Not found

	if (p_current == p_head)
	{// First element matches
		p_head = p_current->nextItem;
	}
	else
	{
		p_previous->nextItem = p_current->nextItem;
	}
	delete p_current;
	
	return p_head;
}

void printList(Item* p_list)
{
	cout << "Printing the list...\n";

	// Traverse the list to print the list
	Item* p_current = p_list;
	while (p_current != nullptr)
	{
		cout << "Item ID: " << p_current->ID << '\n';
		cout << '\n';
		p_current = p_current->nextItem;
	}
	cout << '\n';
}
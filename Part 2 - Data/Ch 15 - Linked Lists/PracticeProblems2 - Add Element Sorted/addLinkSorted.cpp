#include <iostream>

using namespace std;

struct Item
{
	int ID;
	Item* nextItem;
	Item* previousItem;
};

Item* addToSortedLinkedList(Item* p_list, int id);

void printList(Item* p_list);

int main()
{
	Item* p_items = nullptr;
	int IDs[10];
	IDs[0] = 5;
	IDs[1] = 15;
	IDs[2] = 0;
	IDs[3] = 12;
	IDs[4] = -1;
	IDs[5] = 2;
	IDs[6] = 8;
	IDs[7] = 100;
	IDs[8] = 25;
	IDs[9] = 55;
	cout << "The list of items starts with the following IDs...\n";
	for (int i = 0; i < 10; i++)
	{
		cout << IDs[i] << '\n';
	}
	cout << '\n';

	cout << "Create linked list of 10 items...\n";
	for (int i = 0; i < 10; i++)
	{
		p_items = addToSortedLinkedList(p_items, IDs[i]);
	}
	cout << '\n';

	cout << "Ordering the list...\n\n";
	printList(p_items);

	cout << "Testing conditions of equal IDs and adding before first added item on second item...\n";
	p_items = nullptr;
	IDs[1] = 4;
	IDs[2] = 4;
	cout << "The list of items starts with the following IDs...\n";
	for (int i = 0; i < 10; i++)
	{
		cout << IDs[i] << '\n';
	}
	cout << '\n';

	cout << "Create linked list of 10 items...\n";
	for (int i = 0; i < 10; i++)
	{
		p_items = addToSortedLinkedList(p_items, IDs[i]);
	}
	cout << '\n';

	cout << "Ordering the list...\n\n";
	printList(p_items);

	delete p_items;
}

Item* addToSortedLinkedList(Item* p_list, int id)
{
	Item* p_item = new Item;
	p_item->ID = id;

	if (!p_list)
	{// First & only element in the list
		p_item->previousItem = nullptr;
		p_item->nextItem = nullptr;
		return p_item;
	}

	Item* p_current = p_list;
	Item* p_nextItem = p_list->nextItem;
	Item* p_previousItem = p_list->previousItem;
	while (p_current)
	{		
		if ((!p_nextItem && !p_previousItem))
		{ // First addition to the list (second item)
			if(p_current->ID <= p_item->ID)
			{ // Add after the first item
				p_item->previousItem = nullptr;
				p_item->nextItem = p_current;

				p_current->previousItem = p_item;
			}
			else
			{ // Add before the first item
				p_item->previousItem = p_current;
				p_item->nextItem = nullptr;

				p_current->nextItem = p_item;
			}
			break;
		}
		
		if (!p_nextItem && p_previousItem)
		{ // At first element in the list
			if (p_item->ID <= p_current->ID)
			{// Insert before first element
				p_item->previousItem = p_current;
				p_item->nextItem = nullptr;

				p_current->nextItem = p_item;
			}
			else 
			{ // Insert after first element
				p_item->previousItem = p_previousItem;
				p_item->nextItem = p_current;

				p_current->previousItem = p_item;
				p_previousItem->nextItem = p_item;
			}
			
			break;
		}

		if ((!p_previousItem && p_nextItem) &&
			(p_current->ID <= p_item->ID))
		{// Insert after last element in the list
			p_item->previousItem = nullptr;
			p_item->nextItem = p_current;

			p_current->previousItem = p_item;
			break;
		}

		if ((p_previousItem && p_nextItem) &&
			(p_current->ID <= p_item->ID && p_item->ID <= p_previousItem->ID))
		{ // Between current & previous in the middle element in the list
		  // Insert after current element
			p_item->previousItem = p_previousItem;
			p_item->nextItem = p_current;

			p_current->previousItem = p_item;
			p_previousItem->nextItem = p_item;
			break;
		}

		p_previousItem = p_current;
		p_current = p_current->nextItem;
		if (p_current) { p_nextItem = p_current->nextItem; }
	}

	// If not at the head of the list
	if (p_current && p_current->nextItem)
	{// Rewind to the head to return
		p_nextItem = p_current->nextItem;
		while (p_nextItem->previousItem)
		{
			p_nextItem = p_nextItem->previousItem;
		}
		return p_nextItem;
	}
	return p_list;
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
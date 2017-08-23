#include <iostream>
#include <string>

using namespace std;

struct Item
{
	string name;
	Item* nextItem;
	Item* previousItem;
};

Item* addToLinkedList(Item* p_list, string name);
Item* getItemByName(Item* p_list, string name);

void printList(Item* p_list);

int main()
{
	Item* p_items = nullptr;
	string names[10];
	names[0] = "Sam";
	names[1] = "Sally";
	names[2] = "Sue";
	names[3] = "Mark";
	names[4] = "Phil";
	names[5] = "Brenton";
	names[6] = "Melissa";
	names[7] = "Charles";
	names[8] = "Quigly";
	names[9] = "Foo";


	cout << "Create linked list of 10 items...\n";
	for (int i = 0; i < 10; i++)
	{
		p_items = addToLinkedList(p_items, names[i]);
	}

	cout << "Getting element for " << names[3] << "...\n";
	p_items = getItemByName(p_items, names[3]);
	printList(p_items);

	cout << "Getting non-existing name...\n";
	p_items = getItemByName(p_items, "Carmen");
	printList(p_items);

	delete p_items;
}

Item* addToLinkedList(Item* p_list, string name)
{
	Item* p_item = new Item;
	p_item->name = name;
	p_item->previousItem = nullptr;
	p_item->nextItem = p_list;
	if (p_list)
	{
		p_list->previousItem = p_item;
	}


	return p_item;
}

Item* getItemByName(Item* p_list, string name)
{
	Item* p_current = p_list;
	while (p_current != nullptr)
	{
		if (p_current->name == name)
		{
			return p_current;
		}
		p_current = p_current->nextItem;
	}
	return nullptr;
}

void printList(Item* p_list)
{
	if (!p_list)
	{
		cout << "No matching node was returned...\n";
		return;
	}

	cout << "Printing the list...\n";

	// Traverse the list to print the list
	Item* p_current = p_list;
	while (p_current != nullptr)
	{
		cout << "Item Name: " << p_current->name << '\n';
		cout << '\n';
		p_current = p_current->nextItem;
	}
	cout << '\n';
}
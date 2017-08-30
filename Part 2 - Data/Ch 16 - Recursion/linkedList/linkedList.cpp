#include<iostream>

using namespace std;

struct node
{
	int value;
	node* next;
};

// This is an example of 'tail recursion', where the recursive call is the last thing that the function does
node* searchRecursion(node* list, int valueToFind)
{
	cout << "Checking node " << list->value << "... \n";
	if (list == nullptr)
	{
		return nullptr;
	}
	if (list->value == valueToFind)
	{
		return list;
	}
	else
	{
		return searchRecursion(list->next, valueToFind);
	}
}

node* searchLoop(node* list, int valueToFind)
{
	while (true)
	{
		cout << "Checking node " << list->value << "... \n";
		if (list == nullptr)
		{
			return nullptr;
		}
		if (list->value == valueToFind)
		{
			return list;
		}
		else
		{
			list = list->next;
		}
	}
}

node* addToLinkedList(node* p_list, int value)
{
	node* p_item = new node;
	p_item->value = value;
	p_item->next = p_list;

	return p_item;
}

int main()
{
	int maxNode;

	do
	{
		cout << "Please specify a positive value for the linked list to count to:\n";
		cin >> maxNode;
		cout << '\n';
	} while (maxNode < 1);
	
	node* nodes = nullptr;
	for (int i = 1; i <= maxNode; i++)
	{
		nodes = addToLinkedList(nodes, i);
	}

	int valueToFind;
	do
	{
		cout << "Please specify a node number to find that is equal to or less than the number of nodes:\n";
		cin >> valueToFind;
		cout << '\n';
	}
	while ((valueToFind == 0) || (valueToFind > maxNode));
	

	cout << "Result of the recursive function is as follows...\n";
	node* recursiveResult = searchRecursion(nodes, valueToFind);
	cout << "Found node " << recursiveResult->value << "!\n\n";

	cout << "Result of the loop function is as follows...\n";
	node* loopResult = searchLoop(nodes, valueToFind);
	cout << "Found node " << recursiveResult->value << "!\n\n";
}



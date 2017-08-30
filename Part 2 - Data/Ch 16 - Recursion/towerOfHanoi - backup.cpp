#include <iostream>
#include <string>

using namespace std;

// Write a recursive algorithm to solve the Tower of Hanoi problem:
//
// The Tower of Hanoi is a mathematical game or puzzle. 
// It consists of three rods and a number of disks of different sizes, which can slide onto any rod. 
// The puzzle starts with the disks in a neat stack in ascending order of size on one rod, the smallest at the top, thus making a conical shape.
//
// The objective of the puzzle is to move the entire stack to another rod, obeying the following simple rules:
//
// 1. Only one disk can be moved at a time.
// 2. Each move consists of taking the upper disk from one of the stacks and placing it on top of another stack.
// 3. No disk may be placed on top of a smaller disk.
// 
// With 3 disks, the puzzle can be solved in 7 moves.
// The minimal number of moves required to solve a Tower of Hanoi puzzle is 2n - 1, where n is the number of disks.

struct Disc
{
	int size;
	Disc* next;
	Disc* previous;
};

//void towerOfHanoiIterative(Disc* pegA, Disc* pegB, Disc* pegC);
void moveDisc(int discSize, Disc* source, Disc* target, Disc* auxiliary);
Disc* generatePegA(int size);

Disc* removeSmallestDisk(Disc* p_list);
Disc* getSmallestDisk(Disc* p_list);
Disc* getDiskBySize(Disc* p_list, int size);
int getSmallestDiskSize(Disc* p_list);

Disc* addNewToLinkedList(Disc* p_list, int size);
Disc* addToLinkedList(Disc* p_list, Disc* p_item);
Disc* removeFromLinkedList(Disc* p_list, Disc* p_item);

void printList(Disc* p_list);
void printAllLists(Disc* pegA, Disc* pegB, Disc* pegC);

Disc* pegA = nullptr;
Disc* pegB = nullptr;
Disc* pegC = nullptr;

int main()
{
	const int minDiscSize = 2;
	int maxDiscSize = minDiscSize;
	do
	{
		cout << "A column of disks of descending size starting from 1 to n will be generated.\n";
		cout << "Please enter the maximum disk size: ";
		cin >> maxDiscSize;
	} while (maxDiscSize < minDiscSize);

	// Make 3 linked lists that can hold the disks, with 'A' holding the complete set of disks
	pegA = generatePegA(maxDiscSize);
	pegB = nullptr;
	pegC = nullptr;

	printAllLists(pegA, pegB, pegC);

	cout << '\n';
	cout << "Solving the Tower of Hanoi Problem using recursion...\n\n";
	moveDisc(maxDiscSize, pegA, pegC, pegB);

	//cout << '\n';
	//cout << "Solving the Tower of Hanoi Problem using iteration...\n\n";
	//pegA = generatePegA(maxDiskSize);
	//pegB = nullptr;
	//pegC = nullptr;
	//towerOfHanoiIterative(pegA, pegB, pegC);

	delete pegA;
	delete pegB;
	delete pegC;
}

Disc* generatePegA(int size)
{
	Disc* p_items = nullptr;
	for (int i = 1; i <= size; i++)
	{
		p_items = addNewToLinkedList(p_items, i);
	}

	return p_items;
}

void moveDisc(int discSize, Disc* source, Disc* target, Disc* auxiliary)
{
	if (discSize > 0)
	{
		// move n - 1 disks from source to auxiliary, so they are out of the way
		moveDisc(discSize - 1, source, auxiliary, target);

		if(!source)
		{
			cout << "oops";
		}

		// move the nth disk from source to target
		Disc* smallestDisk = removeSmallestDisk(source);
		//target = addToLinkedList(target, smallestDisk);
		target = addToLinkedList(target, smallestDisk);

		////target.append(source.pop());

		// Display our progress
		cout << "Iteration " << discSize << "a";
		//printAllLists(pegA, pegB, pegC);
		printAllLists(source, target, auxiliary);

		// move the n - 1 disks that we left on auxiliary onto target
		moveDisc(discSize - 1, auxiliary, target, source);

		// Display our progress
		cout << "Iteration " << discSize << "b";
		//printAllLists(pegA, pegB, pegC);
		printAllLists(source, target, auxiliary);
	}
}

Disc* removeSmallestDisk(Disc* p_list)
{
	Disc* smallestDisk = getSmallestDisk(p_list);
	p_list = removeFromLinkedList(p_list, smallestDisk);
	return smallestDisk;
}

Disc* getSmallestDisk(Disc* p_list)
{
	return getDiskBySize(p_list, getSmallestDiskSize(p_list));
}

Disc* getDiskBySize(Disc* p_list, int size)
{
	Disc* p_current = p_list;
	while (p_current != nullptr)
	{
		if (p_current->size == size)
		{
			return p_current;
		}
		p_current = p_current->next;
	}
	return nullptr;
}

int getSmallestDiskSize(Disc* p_list)
{
	Disc* p_current = p_list;

	// Determine the minimum size in the list
	int minSize = p_current->size;
	while (p_current != nullptr)
	{
		if (p_current->size < minSize)
		{
			minSize = p_current->size;
		}
		p_current = p_current->next;
	}
	return minSize;
}



Disc* addNewToLinkedList(Disc* p_list, int size)
{
	Disc* p_item = new Disc;
	p_item->size = size;

	return addToLinkedList(p_list, p_item);
}

Disc* addToLinkedList(Disc* p_list, Disc* p_item)
{
	p_item->previous = nullptr;
	p_item->next = p_list;
	if (p_list)
	{
		p_list->previous = p_item;
	}
	else
	{
		p_list = p_item;
	}

	return p_item;
}

Disc* removeFromLinkedList(Disc* p_list, Disc* p_item)
{
	Disc* p_nextItem = p_item->next;
	Disc* p_previousItem = p_item->previous;

	if (!p_nextItem && !p_previousItem)
	{// Only element in the list
		p_item->next = nullptr;
		p_item->previous = nullptr;
		return nullptr;
	}

	if (!p_nextItem && p_previousItem)
	{// First element in the list
		p_previousItem->next = nullptr;

		// Reverse to the head to return
		while (p_previousItem->previous)
		{
			p_previousItem = p_previousItem->previous;
		}

		p_item->next = nullptr;
		p_item->previous = nullptr;
		return p_previousItem;
	}

	if (!p_previousItem && p_nextItem)
	{ // Last element in the list
		p_nextItem->previous = nullptr;
	}
	else if (p_previousItem && p_nextItem)
	{ // Middle element in the list
		p_previousItem->next = p_nextItem;
		p_nextItem->previous = p_previousItem;
	}

	// Rewind to the head to return
	while (p_nextItem->previous)
	{
		p_nextItem = p_nextItem->previous;
	}

	p_item->next = nullptr;
	p_item->previous = nullptr;
	return p_nextItem;
}




void printAllLists(Disc* pegA, Disc* pegB, Disc* pegC)
{
	cout << '\n';
	cout << "Peg A:\n";
	printList(pegA);
	cout << '\n';

	cout << "Peg B:\n";
	printList(pegB);
	cout << '\n';

	cout << "Peg C:\n";
	printList(pegC);
	cout << '\n';
}

void printList(Disc* p_list)
{
	if (!p_list)
	{
		cout << "Disk peg is empty...\n";
		return;
	}

	// Traverse the list to print the list
	Disc* p_current = p_list;
	
	// Fast forward to the tail
	while (p_current->next)
	{
		p_current = p_current->next;
	}

	// Cycle through in reverse
	while (p_current != nullptr)
	{
		cout << "Disk Size: " << p_current->size << '\n';
		p_current = p_current->previous;
	}
	cout << '\n';
}
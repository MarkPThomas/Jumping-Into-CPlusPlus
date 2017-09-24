#pragma once

// For LinkedList Destructor implementation #1
//struct LinkedListNode
//{
//	int val;
//	LinkedListNode* next;
//};

// For LinkedList Destructor implementation #2
class LinkedListNode
{
public:
	// If none is specifed, a default parameterless constructor is automatically generated in compilation.
	~LinkedListNode();	// Destructor
	int val;
	LinkedListNode* next;
};

class LinkedList
{
public:
	LinkedList();										// Constructor
	LinkedList(const LinkedList& other);				// Copy constructor, e.g. for LinkedList list_two(list_one) creating a linked list identical to list_one for list_two.
	~LinkedList();										// Destructor
	LinkedList& operator= (const LinkedList& other);	// Operator overloads for proper copying with a = b;
	

	void insert(int val);	// Adds a node

private:
	LinkedListNode* _head;
	
	void copyList(const LinkedList& other);
};

#include "linkedList.h"

// For LinkedList Destructor implementation #2
LinkedListNode::~LinkedListNode()
{
	delete next;
}


LinkedList::LinkedList()
{
	//  No action taken here
}

LinkedList::LinkedList(const LinkedList& other)
	: _head(nullptr)	// Start off with null in case the other list is empty.
{
	copyList(other);
}

// For LinkedList Destructor implementation #1
//LinkedList::~LinkedList()
//{
//	LinkedListNode* itr = _head;
//	while (itr)
//	{
//		LinkedListNode* tmp = itr->next;
//		delete itr;
//		itr = tmp;
//	}
//}

// For LinkedList Destructor implementation #2
LinkedList::~LinkedList()
{
	delete _head;
}

LinkedList& LinkedList::operator= (const LinkedList& other)
{
	// Make sure we aren't assigning to ourself - we can just ignore if that happens.
	// Notice that we're using 'this' here to ensure that the other value isn't the same address as our object.
	if (this == &other)
	{
		// Return this object to keep the chain of assignments alive
		return *this;
	}

	// Before copying over the new values, we need to free the old memory, since it's no longer used.
	delete _head;
	_head = nullptr;

	copyList(other);
	return *this;
}

void LinkedList::copyList(const LinkedList& other)
{
	LinkedListNode* itr = other._head;
	while (itr)
	{
		insert(itr->val);
	}
}


void LinkedList::insert(int val)
{
	LinkedListNode* node = new LinkedListNode();
	node->val = val;
	node->next = _head;
	_head = node;
}
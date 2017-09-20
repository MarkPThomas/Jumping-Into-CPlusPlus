#include <iostream>
#include "linkedList.h"

using namespace std;

Node* addNode(Node*  list, int value)
{
	Node* newNode = new Node;
	newNode->value = value;
	newNode->next = list;

	return newNode;
}

void printList(const Node* list)
{
	const Node* currentNode = list;
	while (currentNode)
	{
		cout << currentNode->value << endl;
		currentNode = currentNode->next;
	}
}
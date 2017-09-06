#include <cstdlib> 
#include <ctime>
#include <iostream>
#include <string>
#include "binaryTree.h"

using namespace std;

node* createBinaryTree(int numberOfNodes);
void printAsIs(node* tree, string level = "");
void printSorted(node* tree, int numberOfNodes);
void printReverseSorted(node* tree, int numberOfNodes);
void printNode(string level);
void getNodeKeys(node* tree, int numberOfNodes, int nodeKeys[]);

const int maxNumberOfNodes = 100;

int main()
{
	int numberOfNodes = 0;
	while (numberOfNodes <= 0 || numberOfNodes > maxNumberOfNodes)
	{
		cout << "Please specify the number of nodes to create for the binary tree (between 1 and " << maxNumberOfNodes << "):\n";
		cin >> numberOfNodes;
	}
	
	node* tree = createBinaryTree(numberOfNodes);

	// 1. Display the binary tree 'as is'.
	cout << "Display the binary tree 'as is'\n";
	printAsIs(tree);
	cout << '\n';

	// 2. Display tree in sorted order.
	cout << "Display tree in sorted order\n";
	printSorted(tree, numberOfNodes);
	cout << '\n';

	// 3. Display tree in reverse sorted order.
	cout << "Display tree in reverse sorted order\n";
	printReverseSorted(tree, numberOfNodes);
	cout << '\n';

	destroyTree(tree);
}

node* createBinaryTree(int numberOfNodes)
{
	node* tree = nullptr;
	srand(time(nullptr));

	for (int i = 0; i < numberOfNodes; i++)
	{
		tree = insert(tree, rand());
	}

	return tree;
}

void printAsIs(node* tree, string level)
{
	// Print one row at a time, left-to-right
	if (!tree)
	{
		printNode(level + "- ");
		return;
	}
	
	// Print current node
	if (level != "")
	{
		level += "-";
	}
	level += to_string(tree->key);
	printNode(level);

	// Trace left side
	cout << "Left  ";
	printAsIs(tree->left, level);

	// Trace right side
	cout << "Right ";
	printAsIs(tree->right, level);
}

void printSorted(node* tree, int numberOfNodes)
{
	int nodeKeys[maxNumberOfNodes];
	getNodeKeys(tree, numberOfNodes, nodeKeys);

	// Print nodes in order
	for (int i = 0; i < numberOfNodes; i++)
	{
		printNode(to_string(nodeKeys[i]));
	}
}

void printReverseSorted(node* tree, int numberOfNodes)
{
	int nodeKeys[maxNumberOfNodes];
	getNodeKeys(tree, numberOfNodes, nodeKeys);

	// Print nodes in reverse order
	for (int i = 0; i < numberOfNodes; i++)
	{
		printNode(to_string(nodeKeys[numberOfNodes - 1 - i]));
	}
}

void printNode(string level)
{
	cout << "Node: " << level << "\n";
}

void getNodeKeys(node* tree, int numberOfNodes, int nodeKeys[])
{
	int currentCount = 0;

	// Binary tree created only using positive numbers, so we know the minimum value to start with.
	int currentKey = 0;
	while (currentCount < numberOfNodes)
	{
		// Traverse tree and get the next node greater than the current count.
		node* testNode = search(tree, currentKey++);

		if (testNode)
		{
			nodeKeys[currentCount] = testNode->key;
			currentCount++;
		}
	}
}
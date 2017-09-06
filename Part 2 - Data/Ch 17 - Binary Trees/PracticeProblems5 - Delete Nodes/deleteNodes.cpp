#include <cstdlib> 
#include <ctime>
#include <iostream>
#include "binaryTree.h"

using namespace std;

node* createBinaryTree(int numberOfNodes);
int countNodes(node* tree, int count);
node* destroyTreeNonRecursive(node* tree);

int main()
{
	int numberOfNodes = -1;
	while (numberOfNodes < 0)
	{
		cout << "Please specify the number of nodes to create for the binary tree:\n";
		cin >> numberOfNodes;
	}

	node* tree = createBinaryTree(numberOfNodes);

	cout << "The number of nodes in the binary tree is: " << countNodes(tree, 0) << '\n';

	cout << '\n';
	cout << "Deleting all nodes in the binary tree...\n\n";
	tree = destroyTreeNonRecursive(tree);
	cout << "The number of nodes in the binary tree is: " << countNodes(tree, 0) << '\n';
}

node* destroyTreeNonRecursive(node* tree)
{
	node* currentNode = nullptr;
	node* priorNode = nullptr;

	while (tree)
	{
		// Delete root node if it is the only one remaining
		if (!tree->left && !tree->right)
		{
			delete tree;
			tree = nullptr;
			break;
		}

		currentNode = tree;
		priorNode = tree;

		// Delete lowest left node with no children
		while (currentNode->left)
		{
			priorNode = currentNode;
			currentNode = currentNode->left;
		}
		if (!currentNode->right)
		{
			delete currentNode;
			priorNode->left = nullptr;
		}
		else // Delete the lowest right node with no children
		{
			while (currentNode->right)
			{
				priorNode = currentNode;
				currentNode = currentNode->right;
			}
			delete currentNode;
			priorNode->right = nullptr;
		}
	}
	return tree;
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

int countNodes(node* tree, int count)
{
	if (!tree)
	{
		return count;
	}

	count = countNodes(tree->left, count);
	count = countNodes(tree->right, count);

	return count + 1;
}
#include <cstdlib> 
#include <ctime>
#include <iostream>
#include <string>
#include "binaryTree.h"

using namespace std;

node* createBinaryTree(int numberOfNodes);
int countNodes(node* tree, int count);

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
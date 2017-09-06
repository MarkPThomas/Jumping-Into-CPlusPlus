#include <iostream>
#include <string>
#include "binaryTree.h"

using namespace std;

void checkTreeBalanced(node* tree);
node* createBalancedBinaryTree();
node* createUnbalancedBinaryTree();
bool isTreeBalanced(node* tree);
int countNodes(node* tree, int count);

int main()
{
	cout << "\n==== Balanced Tree ====\n";
	cout << "Creating a balanced binary tree...\n";
	node* balancedTree = createBalancedBinaryTree();
	checkTreeBalanced(balancedTree);
	destroyTree(balancedTree);
	cout << '\n';

	cout << "\n==== Unbalanced Tree ====\n";
	cout << "Creating an unbalanced binary tree...\n";
	node* unbalancedTree = createUnbalancedBinaryTree();
	checkTreeBalanced(unbalancedTree);
	destroyTree(unbalancedTree);
	cout << '\n';
}

void checkTreeBalanced(node* tree)
{
	cout << "Checking if the tree is balanced.\n\n";
	cout << "This means that there are an equal number of nodes in the left and right branches of child nodes.\n\n";

	if (isTreeBalanced(tree))
	{
		cout << "The tree is balanced.\n";
	}
	else
	{
		cout << "The tree is not balanced!\n";
	}
	cout << "# of nodes in the following branches:\n";
	cout << "Left:  " << countNodes(tree->left, 0) << '\n';
	cout << "Right: " << countNodes(tree->right, 0) << '\n';
}

node* createBalancedBinaryTree()
{
	node* tree = nullptr;
	tree = insert(tree, 10);
	tree = insert(tree, 6);
	tree = insert(tree, 14);
	tree = insert(tree, 5);
	tree = insert(tree, 8);
	tree = insert(tree, 11);
	tree = insert(tree, 18);
	return tree;
}

node* createUnbalancedBinaryTree()
{
	node* tree = nullptr;
	tree = insert(tree, 10);
	tree = insert(tree, 6);
	tree = insert(tree, 14);
	tree = insert(tree, 5);
	tree = insert(tree, 8);
	return tree;
}

bool isTreeBalanced(node* tree)
{
	int leftTree = countNodes(tree->left, 0);
	int rightTree = countNodes(tree->right, 0);

	return (leftTree == rightTree);
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
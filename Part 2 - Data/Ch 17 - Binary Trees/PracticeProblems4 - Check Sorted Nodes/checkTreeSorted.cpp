#include <iostream>
#include <string>
#include "binaryTree.h"

using namespace std;

void checkTreeSorted(node* tree);
node* createSortedBinaryTree();
node* createUnsortedBinaryTree();
bool isTreeSorted(node* tree);

int main()
{
	cout << "\n==== Sorted Tree ====\n";
	cout << "Creating a sorted binary tree...\n";
	node* sortedTree = createSortedBinaryTree();
	checkTreeSorted(sortedTree);
	destroyTree(sortedTree);

	cout << "\n==== Unsorted Tree ====\n";
	cout << "Creating an unsorted binary tree...\n";
	node* unsortedTree = createUnsortedBinaryTree();
	checkTreeSorted(unsortedTree);
	destroyTree(unsortedTree);
}

void checkTreeSorted(node* tree)
{
	cout << "Checking if the tree is properly sorted.\n\n";
	cout << "This means that all nodes to the left of a given node are less than the value of that node, and all nodes to the right of a given node are greater than the value of that node.\n\n";

	if (isTreeSorted(tree))
	{
		cout << "The tree is properly sorted!\n\n";
	}
	else
	{
		cout << "The tree is not properly sorted!\n\n";
	}
}

node* createSortedBinaryTree()
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

node* createUnsortedBinaryTree()
{
	// Create a tree that is sorted.
	node* tree = nullptr;
	tree = insert(tree, 10);
	tree = insert(tree, 6);
	tree = insert(tree, 14);
	tree = insert(tree, 5);
	tree = insert(tree, 8);
	tree = insert(tree, 11);
	tree = insert(tree, 18);

	// Manually change the keys in order to ensure an unsorted tree (insertion/deletion may re-sort the tree)
	node* unbalancedNode = search(tree, 5);
	unbalancedNode->key = 7;
	
	return tree;
}

bool isTreeSorted(node* tree)
{
	// Sorted if the node is null
	if (!tree)
	{
		return true;
	}

	// Sorted if both children are null
	if (!tree->left &&
		!tree->right)
	{
		return true;
	}

	// Check if current node is sorted with children:
	// Balanced if left child is less than current value
	if (tree->left && tree->left->key > tree->key)
	{
		cout << "Left Child = " << tree->left->key << " > " << tree->key << '\n';
		return false;
	}

	// Balanced if right child is greater than current value
	if (tree->right && tree->right->key < tree->key)
	{
		cout << "Right Child = " << tree->right->key << " < " << tree->key << '\n';
		return false;
	}	

	// Check if children are sorted:
	return (isTreeSorted(tree->left) &&
			isTreeSorted(tree->right));
}
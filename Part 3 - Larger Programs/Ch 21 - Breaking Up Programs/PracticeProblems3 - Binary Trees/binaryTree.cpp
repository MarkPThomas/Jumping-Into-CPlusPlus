#include <cstdlib> 
#include <ctime>
#include <iostream>
#include "binaryTree.h"

using namespace  std;


node* insert(node* tree, int key)
{
	// Base case - we have reached an empty tree and need to insert our new node here
	if (!tree)
	{
		node* newTree = new node;
		newTree->left = nullptr;
		newTree->right = nullptr;
		newTree->key = key;
		return newTree;
	}

	// Decide whether to insert into the left subtree or the right subtree.
	// This depends on the value of the node.
	if (key < tree->key)
	{
		// Build a new tree based on tree->left by adding the key.
		// Then replace the existing tree->left pointer with a pointer to the new tree.
		// We need to set the tree->left pointer in case tree->left is null.
		// (If it isn't null, tree->left won't actually change, but it doesn't hurt to set it.)
		tree->left = insert(tree->left, key);
	}
	else
	{
		// Insertion int the right is exactly symmetric to insertion into the left
		tree->right = insert(tree->right, key);
	}
	return tree;
}

node* search(node* tree, int key)
{
	// If we reach the empty tree, clearly it's not here!
	if (!tree)
	{
		return nullptr;
	}

	// If we find the key, we're done!
	if (key == tree->key)
	{
		return tree;
	}

	// Otherwise, try looking in either the left or right subtree
	if (key < tree->key)
	{
		return search(tree->left, key);
	}
	return search(tree->right, key);
}

void destroyTree(node* tree)
{
	if (tree)
	{
		destroyTree(tree->left);
		destroyTree(tree->right);
		delete tree;
	}
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

node* remove(node* tree, int key)
{
	if (!tree)
	{
		return nullptr;
	}

	if (key == tree->key)
	{
		// What to do?
		// Three cases:
		// 1. The node being removed has no children.
		// 2. The node being removed has one child.
		// 3. The node being removed has two children.

		// The first two cases handle having 0 or 1 child node.
		if (!tree->left)
		{
			node* rightSubtree = tree->right;
			delete tree;

			// This might return null if there are 0 child nodes, but that is what we want anyway.
			return rightSubtree;
		}

		if (!tree->right)
		{
			node* leftSubtree = tree->left;
			delete tree;

			// This will always return a valid node, since we know tree->left is not null from the previous 'if' statement.
			return leftSubtree;
		}

		// The other case handles having more than 1 child node.
		node* maxNode = findMax(tree->left);

		// Since maxNode came from the left subtree, 
		// we need to remove it from that subtree before re-linking that subtree back into the rest of the tree.
		maxNode->left = removeMaxNode(tree->left, maxNode);
		maxNode->right = tree->right;
		delete tree;
		return maxNode;
	}

	if (key < tree->key)
	{
		tree->left = remove(tree->left, key);
	}
	else
	{
		tree->right = remove(tree->right, key);
	}
	return tree;
}

node* findMax(node* tree)
{
	if (!tree)
	{
		return nullptr;
	}

	if (!tree->right)
	{
		return tree;
	}
	return  findMax(tree->right);
}

node* removeMaxNode(node* tree, node* maxNode)
{
	// Defensive coding. Shouldn't actually hit this.
	if (!tree)
	{
		return  nullptr;
	}

	// We found the node, now we can replace it
	if (tree == maxNode)
	{
		// The only reason we can do this is beacuse we know maxNode->right is null, so we aren't losing any information.
		// If maxNode has no left subtree, then we wll just return null from this branch, 
		//   which will result in maxNode being replaced with an empty tree, which is what we want.
		return maxNode->left;
	}

	// Each recursive call replaces the right subtree tree with a new subtree that doesn't contain maxNode.
	tree->right = removeMaxNode(tree->right, maxNode);
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

bool isTreeBalanced(node* tree)
{
	int leftTree = countNodes(tree->left, 0);
	int rightTree = countNodes(tree->right, 0);

	return (leftTree == rightTree);
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


node* createRandomBinaryTree(int numberOfNodes)
{
	node* tree = nullptr;
	srand(time(nullptr));

	for (int i = 0; i < numberOfNodes; i++)
	{
		tree = insert(tree, rand());
	}

	return tree;
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

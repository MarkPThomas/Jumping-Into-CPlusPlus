#include <iostream>
#include <string>
#include "binaryTree.h"

using namespace  std;

void printSortedTreeNodes();
void countTreeNodes();
void checkTreeBalanceStates();
void checkTreeSortedStates();
void deleteNodes();

int main()
{
	while (true)
	{
		int choice;
		bool validChoice = false;
		while (!validChoice)
		{
			cout << "Select from the following options for Binary Trees:\n";
			cout << "0. Exit\n";
			cout << "1. Print Nodes\n";
			cout << "2. Count Nodes\n";
			cout << "3. Check Balanced Tree\n";
			cout << "4. Check Sorted Tree\n";
			cout << "5. Delete Nodes\n";
			cin >> choice;
			if (choice == 0)
			{
				return 0;
			}
			validChoice = (0 <= choice && choice <= 5);
			if (!validChoice)
			{
				cout << "Please select a valid choice.\n";
			}
		}

		switch (choice)
		{
		case 1: 
			printSortedTreeNodes();
			break;
		case 2:
			countTreeNodes();
			break;
		case 3:
			checkTreeBalanceStates();
			break;
		case 4:
			checkTreeSortedStates();
			break;
		case 5:
			deleteNodes();
			break;
		default:
			break;
		}
		
	}
}

void printSortedTreeNodes()
{
	int numberOfNodes = 0;
	while (numberOfNodes <= 0 || numberOfNodes > maxNumberOfNodes)
	{
		cout << "Please specify the number of nodes to create for the binary tree (between 1 and " << maxNumberOfNodes << "):\n";
		cin >> numberOfNodes;
	}

	node* tree = createRandomBinaryTree(numberOfNodes);

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

void countTreeNodes()
{
	int numberOfNodes = -1;
	while (numberOfNodes < 0)
	{
		cout << "Please specify the number of nodes to create for the binary tree:\n";
		cin >> numberOfNodes;
	}

	node* tree = createRandomBinaryTree(numberOfNodes);

	cout << "The number of nodes in the binary tree is: " << countNodes(tree, 0) << '\n';

	destroyTree(tree);
}

void checkTreeBalanceStates()
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

void checkTreeSortedStates()
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

void deleteNodes()
{
	int numberOfNodes = -1;
	while (numberOfNodes < 0)
	{
		cout << "Please specify the number of nodes to create for the binary tree:\n";
		cin >> numberOfNodes;
	}

	node* tree = createRandomBinaryTree(numberOfNodes);

	cout << "The number of nodes in the binary tree is: " << countNodes(tree, 0) << '\n';

	cout << '\n';
	cout << "Deleting all nodes in the binary tree using a non-recursive function...\n\n";
	tree = destroyTreeNonRecursive(tree);
	cout << "The number of nodes in the binary tree is: " << countNodes(tree, 0) << '\n';
}
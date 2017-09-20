#pragma once
#include <string>

using namespace std;

//extern const int maxNumberOfNodes = 100;
static const int maxNumberOfNodes = 100;

struct node
{
	int key;
	node* left;
	node* right;
};

node* insert(node* tree, int key);
node* search(node* tree, int key);
void destroyTree(node* tree);
node* destroyTreeNonRecursive(node* tree);
node* remove(node* tree, int key);
node* findMax(node* tree);
node* removeMaxNode(node* tree, node* maxNode);

int countNodes(node* tree, int count);
void getNodeKeys(node* tree, int numberOfNodes, int nodeKeys[]);

void checkTreeBalanced(node* tree);
bool isTreeBalanced(node* tree);

void checkTreeSorted(node* tree);
node* createSortedBinaryTree();
node* createUnsortedBinaryTree();
bool isTreeSorted(node* tree);


node* createRandomBinaryTree(int numberOfNodes);
node* createBalancedBinaryTree();
node* createUnbalancedBinaryTree();

void printAsIs(node* tree, string level = "");
void printSorted(node* tree, int numberOfNodes);
void printReverseSorted(node* tree, int numberOfNodes);
void printNode(string level);



#include <string>

using namespace std;

struct node
{
	string key;
	string value;
	node* left;
	node* right;
};

node* insert(node* map, string key, string value);
node* search(node* map, string key);
string getValue(node* map, string key);
void destroyMap(node* map);
node* remove(node* map, string key);
node* findMax(node* map);
node* removeMaxNode(node* map, node* maxNode);


node* insert(node* map, string key, string value)
{
	// Base case - we have reached an empty tree and need to insert our new node here
	if (!map)
	{
		node* newTree = new node;
		newTree->left = nullptr;
		newTree->right = nullptr;
		newTree->key = key;
		newTree->value = value;
		return newTree;
	}

	// Alternate base case - we have reached an existing node. Value is to be modified.
	if (key == map->key)
	{
		map->value = value;
		return map;
	}

	// Decide whether to insert into the left subtree or the right subtree.
	// This depends on the value of the node.
	if (key < map->key)
	{
		// Build a new tree based on tree->left by adding the key.
		// Then replace the existing tree->left pointer with a pointer to the new tree.
		// We need to set the tree->left pointer in case tree->left is null.
		// (If it isn't null, tree->left won't actually change, but it doesn't hurt to set it.)
		map->left = insert(map->left, key, value);
	}
	else
	{
		// Insertion int the right is exactly symmetric to insertion into the left
		map->right = insert(map->right, key, value);
	}
	return map;
}

node* search(node* map, string key)
{
	// If we reach the empty tree, clearly it's not here!
	if (!map)
	{
		return nullptr;
	}

	// If we find the key, we're done!
	if (key == map->key)
	{
		return map;
	}

	// Otherwise, try looking in either the left or right subtree
	if (key < map->key)
	{
		return search(map->left, key);
	}
	return search(map->right, key);
}

string getValue(node* map, string key)
{
	node* result = search(map, key);
	if(result)
	{
		return result->value;
	}
	return "";
}

void destroyMap(node* map)
{
	if (map)
	{
		destroyMap(map->left);
		destroyMap(map->right);
		delete map;
	}
}

node* remove(node* map, string key)
{
	if (!map)
	{
		return nullptr;
	}

	if (key == map->key)
	{
		// What to do?
		// Three cases:
		// 1. The node being removed has no children.
		// 2. The node being removed has one child.
		// 3. The node being removed has two children.

		// The first two cases handle having 0 or 1 child node.
		if (!map->left)
		{
			node* rightSubtree = map->right;
			delete map;

			// This might return null if there are 0 child nodes, but that is what we want anyway.
			return rightSubtree;
		}

		if (!map->right)
		{
			node* leftSubtree = map->left;
			delete map;

			// This will always return a valid node, since we know tree->left is not null from the previous 'if' statement.
			return leftSubtree;
		}

		// The other case handles having more than 1 child node.
		node* maxNode = findMax(map->left);

		// Since maxNode came from the left subtree, 
		// we need to remove it from that subtree before re-linking that subtree back into the rest of the tree.
		maxNode->left = removeMaxNode(map->left, maxNode);
		maxNode->right = map->right;
		delete map;
		return maxNode;
	}

	if (key < map->key)
	{
		map->left = remove(map->left, key);
	}
	else
	{
		map->right = remove(map->right, key);
	}
	return map;
}

node* findMax(node* map)
{
	if (!map)
	{
		return nullptr;
	}

	if (!map->right)
	{
		return map;
	}
	return  findMax(map->right);
}

node* removeMaxNode(node* map, node* maxNode)
{
	// Defensive coding. Shouldn't actually hit this.
	if (!map)
	{
		return  nullptr;
	}

	// We found the node, now we can replace it
	if (map == maxNode)
	{
		// The only reason we can do this is beacuse we know maxNode->right is null, so we aren't losing any information.
		// If maxNode has no left subtree, then we wll just return null from this branch, 
		//   which will result in maxNode being replaced with an empty tree, which is what we want.
		return maxNode->left;
	}

	// Each recursive call replaces the right subtree tree with a new subtree that doesn't contain maxNode.
	map->right = removeMaxNode(map->right, maxNode);
	return map;
}


struct node
{
	int key;
	node* left;
	node* right;
};

node* insert(node* tree, int key);
node* search(node* tree, int key);
void destroyTree(node* tree);
node* remove(node* tree, int key);
node* findMax(node* tree);
node* removeMaxNode(node* tree, node* maxNode);


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
	if(key < tree->key)
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
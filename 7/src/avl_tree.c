#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree_impl.h"
#include "avl_tree.h"

tree_node_t *rotate_left(tree_node_t *node)
{
	tree_node_t *tmp = node->right;
	node->right = tmp->left;
	tmp->left = node;
	return tmp;
}

tree_node_t *rotate_right(tree_node_t *node)
{
	tree_node_t *tmp = node->left;
	node->left = tmp->right;
	tmp->right = node;
	return tmp;
}

int height(tree_node_t *root)
{
	if (!root)
		return 0;
	int hleft = 0, hright = 0;
	if (root && root->left)
		hleft = height(root->left);
	if (root && root->right)
		hright = height(root->right);
	return (hleft < hright) ? hright + 1 : hleft + 1;
}

tree_node_t *balance(tree_node_t *tree)
{
	if (!tree)
		return NULL;
	int bfactor = height(tree->right) - height(tree->left);
	if (bfactor < -1)
	{
		bfactor = height(tree->left->right) - height(tree->left->left);
		if (bfactor > 0)
			tree->left = rotate_left(tree->left);
		return rotate_right(tree);
		
	}
	else if (bfactor > 1)
	{
		bfactor = height(tree->right->right) - height(tree->right->left);
		if (bfactor < 0)
			tree->right = rotate_right(tree->right);
		return rotate_left(tree);
	}
	return tree;
}

tree_node_t *tree_balance(tree_node_t *tree)
{
	if (!tree)
		return NULL;
	
	if (tree->left)
		tree->left = tree_balance(tree->left);
	
	if (tree->right)
		tree->right = tree_balance(tree->right);
	
	while (abs(height(tree->right) - height(tree->left)) > 1)
		tree = balance(tree);
	
	if (tree->left)
		tree->left = tree_balance(tree->left);
		
	if (tree->right)
		tree->right = tree_balance(tree->right);
	
	return tree;
}
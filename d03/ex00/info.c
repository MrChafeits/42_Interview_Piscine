#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "header.h"

typedef struct s_node t_node;
typedef struct s_info t_info;

int getMin(t_node *root)
{
	if (!root)
		return INT_MAX;
	int ret = root->value;
	int left = getMin(root->left);
	int right = getMin(root->right);
	if (left < ret)
		ret = left;
	if (right < ret)
		ret = right;
	return ret;
}

int getMax(t_node *root)
{
	if (!root)
		return INT_MIN;
	int ret = root->value;
	int left = getMax(root->left);
	int right = getMax(root->right);
	if (left > ret)
		ret = left;
	if (right > ret)
		ret = right;
	return ret;
}

static int getElem(t_node *root)
{
	if (!root)
		return 0;
	return 1 + getElem(root->left) + getElem(root->right);
}

int isBST(t_node *root)
{
	if (!root)
		return 1;
	if (root->left && root->value < root->left->value)
		return 0;
	if (root->right && root->value > root->right->value)
		return 0;
	if (!isBST(root->left) || !isBST(root->right))
		return 0;
	return 1;
}

static int max2(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

static int depth(t_node *root)
{
	if (!root)
		return 0;
	return 1 + max2(depth(root->left), depth(root->right));
}

int isBalanced(t_node *root)
{
	if (!root)
		return 1;
	int left = depth(root->left);
	int right = depth(root->right);
	return abs(left - right) <= 1 && isBalanced(root->left) && isBalanced(root->right);
}

t_info   getInfo(t_node *root)
{
	t_info res;

	res.min = getMin(root);
	res.max = getMax(root);
	res.elements = getElem(root);
	res.height = depth(root);
	res.isBST = isBST(root);
	res.isBalanced = isBalanced(root);
	return res;
}

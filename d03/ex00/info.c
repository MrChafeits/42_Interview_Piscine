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
	int ret, left, right;

	if (root == 0)
		return INT_MAX;
	ret = root->value;
	left = getMin(root->left);
	right = getMin(root->right);
	if (left < ret)
		ret = left;
	if (right < ret)
		ret = right;
	return ret;
}

int getMax(t_node *root)
{
	int ret, right, left;

	if (root == 0)
		return INT_MIN;
	ret = root->value;
	left = getMax(root->left);
	right = getMax(root->right);
	if (left > ret)
		ret = left;
	if (right > ret)
		ret = right;
	return ret;
}

static int getElem(t_node *root)
{
	if (root == 0)
		return 0;
	return 1 + getElem(root->left) + getElem(root->right);
}

int isBST(t_node *root)
{
	if (root == 0)
		return 1;
	if (root->left && root->value < root->left->value)
		return 0;
	if (root->right && root->value > root->right->value)
		return 0;
	if (isBST(root->left) == 0 || isBST(root->right) == 0)
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
	if (root == 0)
		return 0;
	return 1 + max2(depth(root->left), depth(root->right));
}

int isBalanced(t_node *root)
{
	int left, right;

	if (root == 0)
		return 1;
	left = depth(root->left);
	right = depth(root->right);
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include "header.h"

typedef struct s_node t_node;
t_node *newNode(int v)
{
	t_node *new = malloc(sizeof(t_node));

	if (new == 0)
		return 0;
	new->left = new->right = 0;
	new->value = v;
	return new;
}

/* A function that constructs Balanced Binary Search Tree from a sorted array */
t_node	*sortedArrayToBST(int *arr, int start, int end)
{
	int mid;
	t_node *root;

	if (start > end)
		return NULL;
	mid = (start + end) / 2;
	root = newNode(arr[mid]);
	/* fprintf(stderr, "[DBG: start(%d) mid(%d) end(%d)]\n", start, mid, end); */
	root->left =  sortedArrayToBST(arr, start, mid - 1);
	root->right = sortedArrayToBST(arr, mid + 1, end);
	return root;
}

t_node *createBST(int *arr, int n)
{
	return sortedArrayToBST(arr, 0, n-1);
}

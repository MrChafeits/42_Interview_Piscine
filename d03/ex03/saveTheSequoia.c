#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

typedef struct s_node t_node;
extern void printBinaryTree(t_node *root);
#if 0
struct s_node {
	int value;
	struct s_node *right;
	struct s_node *left;
};
#endif

static void	swap_nodes(t_node **a, t_node **b)
{
	t_node *tmp = *a;
	t_node *left = (*b)->left;
	t_node *right = (*b)->right;

	*a = *b;
	if (tmp->left == (*b)) {
		(*b)->left = tmp;
		(*b)->right = tmp->right;
	} else {
		(*b)->left = tmp->left;
		(*b)->right = tmp;
	}
	tmp->left = left;
	tmp->right = right;
}

static void	swooce(t_node **root)
{
	ack++;
	if (root == 0 || *root == 0)
		return;

	if ((*root)->left && (*root)->left->value > (*root)->value) {
		lswaps++;
		swap_nodes(root, &(*root)->left);
	}

	if ((*root)->right && (*root)->right->value > (*root)->value) {
		rswaps++;
		swap_nodes(root, &(*root)->right);
	}

	swooce(&(*root)->left);
	swooce(&(*root)->right);
}

static int	total(t_node *root)
{
	if (root == 0)
		return 0;

	return 1 + total(root->left) + total(root->right);
}

void	saveTheSequoia(t_node **root)
{
	ack = lswaps = rswaps = 0;
	int i;

	if (root == 0 || *root == 0)
		return;

	i = total(*root) / 2;
	/* printf("\ni(%d)\n", i); */
	while (--i)
		swooce(root);
	/* printf("ack(%d)\n", ack); */
	/* printf("lswaps(%d)\n", lswaps); */
	/* printf("rswaps(%d)\n", rswaps); */
}

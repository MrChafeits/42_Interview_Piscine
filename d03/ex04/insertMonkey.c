#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "header.h"

typedef struct s_node t_node;
typedef struct s_qnod t_qnod;
struct s_qnod {
	t_node **cnt;
	t_qnod *next;
};
typedef struct s_queue Queue;
struct s_queue {
	t_qnod *first, *last;
};

Queue *createQueue(void)
{
	Queue *q = malloc(sizeof(Queue));
	assert(q != 0);
	q->first = q->last = 0;
	return q;
}
void Enqueue(Queue *q, t_node **cnt)
{
	t_qnod *new;

	if (q) {
		new = malloc(sizeof(*new));
		assert(new != 0);
		new->cnt = cnt;
		new->next = 0;
		if (!q->first)
			q->first = new;
		else
			q->last->next = new;
		q->last = new;
	}
}
t_node **Dequeue(Queue *q)
{
	t_qnod *tmp;
	t_node **ret = 0;

	if (q && q->first) {
		if (q->first == q->last)
			q->last = 0;
		tmp = q->first;
		ret = tmp->cnt;
		q->first = tmp->next;
		free(tmp);
	}
	return ret;
}
t_node **peek(Queue *q)
{
	if (!q || !q->first)
		return 0;
	return q->first->cnt;
}
int isEmpty(Queue *q) { return !q || !q->first; }

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

static void	heapify(t_node **root)
{
	if (root == 0 || *root == 0)
		return;

	if ((*root)->left && (*root)->left->value > (*root)->value)
		swap_nodes(root, &(*root)->left);

	if ((*root)->right && (*root)->right->value > (*root)->value)
		swap_nodes(root, &(*root)->right);

	heapify(&(*root)->left);
	heapify(&(*root)->right);
}

static int	total(t_node *root)
{
	if (root == 0)
		return 0;

	return 1 + total(root->left) + total(root->right);
}

void otherInsert(t_node **root, t_node *new, int *flag)
{
	int lt=0, rt=0;
	if (*flag == 1 || root == 0 || *root == 0 || new == 0)
		return;

	if ((*root)->left)
		otherInsert(&(*root)->left, new, flag);

	if ((*root)->right)
		otherInsert(&(*root)->right, new, flag);

	lt = total((*root)->left);
	rt = total((*root)->right);
	if (lt <= rt) {
		(*root)->left = new;
		*flag = 1;
	} else {
		(*root)->right = new;
		*flag = 1;
	}
	/* if ((*root)->left == 0 && (*root)->right == 0) { */
	/* 	(*root)->left = new; */
	/* 	*flag = 1; */
	/* } */
}
#if 1
void insertMonkey(t_node **root, t_node *new)
{
	if (!*root)
		*root = new;
	else {
		Queue *q = createQueue();
		Enqueue(q, root);
		while (!isEmpty(q)) {
			t_node **tmp = Dequeue(q);
			if (!*tmp) {
				*tmp = new;
				break;
			} else {
				Enqueue(q, &(*tmp)->left);
				Enqueue(q, &(*tmp)->right);
			}
		}
	}
	heapify(root);
}
#else
void	insertMonkey(t_node **root, t_node *monkey)
{
	int i, lsize, rsize, flag = 0;

	if (root == 0 || *root == 0)
		return;

	if ((*root)->left && (*root)->right) {
		lsize = total((*root)->left);
		rsize = total((*root)->right);
		if (lsize <= rsize)
			otherInsert(&(*root)->left, monkey, &flag);
		else
			otherInsert(&(*root)->right, monkey, &flag);
	} else {
		otherInsert(root, monkey, &flag);
	}
	i = total(*root) / 2;
	while (--i) {
		heapify(root);
	}
}
#endif

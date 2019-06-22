#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>

/* Create a balanced binary search tree.
 * Hooray. */

typedef struct s_node t_node;
#if 0
struct s_node {
    int value;
    struct s_node *right, *left;
};
#endif

static t_node *nn(int v)
{
    t_node *n = calloc(1, sizeof(*n));

    if (n == 0)
        return 0;
    n->value = v;
    return n;
}

static t_node *arrToBST(int *arr, int start, int end)
{
    t_node *root;
    int mid;

    if (start > end)
        return 0;
    mid = (start + end) / 2;
    root = nn(arr[mid]);
    root->left = arrToBST(arr, start, mid - 1);
    root->right = arrToBST(arr, mid + 1, end);
    return root;
}

t_node *createBST(int *arr, int n)
{
    if (arr == 0 || n <= 0)
        return 0;
    return arrToBST(arr, 0, n - 1);
}

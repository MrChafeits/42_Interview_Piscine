#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

typedef struct s_node t_node;
#if 0
struct s_node {
	int value;
	struct s_node *right;
	struct s_node *left;
};
#endif
void	saveTheSequoia(t_node **root)
{
	if (root == 0 || *root == 0)
		return;
}

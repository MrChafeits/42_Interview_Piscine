#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

typedef struct s_node t_node;

#if 0
struct s_node {
	char	*name;
	struct s_node **children;
};
#endif

static int search(t_node *root, t_node **fnd, char *one, char *two)
{
	int cnt, i;
	if (root == 0)
		return 0;
	cnt = 0;
	if (strcmp(root->name, one) == 0 || strcmp(root->name, two) == 0)
		cnt++;
	for (i = 0; root->children[i] != 0; i++)
		cnt += search(root->children[i], fnd, one, two);
	if (cnt == 2 && *fnd == 0)
		*fnd = root;
	return cnt;
}

t_node *findParent(t_node *root, char *firstSpecies, char *secondSpecies)
{
	t_node *fnd = 0;

	search(root, &fnd, firstSpecies, secondSpecies);
	return fnd;
}

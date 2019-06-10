#include <string.h>
#include "header.h"

/* Binary search, for the leftmost element */

int searchPrice(t_art **arts, int n, char *name)
{
	int left, right, res, i;

	if (arts == 0 || *arts == 0 || name == 0)
		return -1;
	left = 0;
	right = n;
	while (left < right) {
		i = (left + right) / 2;
		if (strcmp(arts[i]->name, name) < 0)
			left = i + 1;
		else
			right = i;
	}
	res = left;
	if (strcmp(arts[res]->name, name) == 0)
		return arts[res]->price;
	else
		return -1;
}

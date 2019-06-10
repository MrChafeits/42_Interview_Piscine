#include <string.h>
#include "header.h"

int searchPrice(struct s_art **arts, char *name)
{
	register int i;

	for (i = 0; arts[i] != NULL; i++)
		if (strcmp(arts[i]->name, name) == 0)
			return arts[i]->price;
	return -1;
}

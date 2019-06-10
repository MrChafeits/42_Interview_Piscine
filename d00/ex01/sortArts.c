#include <string.h>
#include "header.h"

/* #define SWAP(a, b) */

int partition(struct s_art **arts, int lo, int hi)
{
	struct s_art *piv, *tmp = 0;
	int i, j;

	piv = arts[lo + (hi - lo) / 2];
	i = lo - 1;
	j = hi + 1;
	for (;;) {
		do {
			i++;
		} while (strcmp(arts[i]->name, piv->name) < 0);
		do {
			j--;
		} while (strcmp(arts[j]->name, piv->name) > 0);
		if (i >= j)
			return j;
		tmp = arts[j];
		arts[j] = arts[i];
		arts[i] = tmp;
	}
}

void quick_sort(struct s_art **arts, int lo, int hi)
{
	int p;

	if (lo < hi) {
		p = partition(arts, lo, hi);
		quick_sort(arts, lo, p);
		quick_sort(arts, p + 1, hi);
	}
}

int length(struct s_art **arts)
{
	register int i;

	if (arts == 0 || *arts == 0)
		return 0;
	for (i = 0; arts[i] != 0; i++);
	return i;
}

void sortArts(struct s_art **arts)
{
	int lo, hi;
	if (arts == 0 || *arts == 0) return;
	lo = 0;
	hi = length(arts) - 1;
	quick_sort(arts, lo, hi);
}

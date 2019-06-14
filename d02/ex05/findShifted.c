#include <stdio.h>
#include "header.h"

static int	binsearch(int *rocks, int l, int r, int v)
{
	int m = l + (r - l) / 2;

	if (l > r)
		return -1;
	if (rocks[m] == v)
		return m;
	if (rocks[l] <= rocks[m]) {
		if (rocks[l] <= v && v <= rocks[m])
			return binsearch(rocks, l, m - 1, v);
		else
			return binsearch(rocks, m + 1, r, v);
	} else {
		if (rocks[m] <= v && v <= rocks[r])
			return binsearch(rocks, m + 1, r, v);
		else
			return binsearch(rocks, l, m - 1, v);
	}
}

int			searchShifted(int *rocks, int length, int value)
{
	int s = binsearch(rocks, 0, length - 1, value);

	if (s == -1)
		return -1;
	while (s >= 0 && rocks[s] == value)
		s--;
	return s + 1;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"

/*
height:			hairColor:	eyeColor:
0 - 140-149		0 - black 	0 - amber
1 - 150-159		1 - brown 	1 - blue
2 - 160-169		2 - blond 	2 - brown
3 - 170-179		3 - auburn	3 - gray
4 - 180-189		4 - red   	4 - green
5 - 190-199		5 - gray  	5 - hazel
6 - 200-209		6 - white 	6 - red
7 - 210-219					7 - violet
8 - 220-229

gender:   	glasses: 	tattoo:		piercing:
0 - male  	0 - false	0 - false	0 - false
1 - female	1 - true	1 - true	1 - true

description =  gender * 10^6 + height * 10^5 + hairColor * 10^4 +
eyeColor * 10^3 + glasses * 10^2 + tattoo * 10^1 + piercing * 10^0
*/

int getDescription(t_info *info)
{
	int ret = 0;

	if (info == 0)
		return 0;
	ret = (info->gender    * 1000000)
		+ (info->height    * 100000)
		+ (info->hairColor * 10000)
		+ (info->eyeColor  * 1000)
		+ (info->glasses   * 100)
		+ (info->tattoo    * 10)
		+ (info->piercing  * 1);
	return ret;
}

static int getmax(t_criminal **arr, int n)
{
	int mx = arr[0]->description;
	int i;

	for (i = 1; i < n; i++)
		if (arr[i]->description > mx)
			mx = arr[i]->description;
	return mx;
}

static void countySnoodle(t_criminal **arr, int n, int dig)
{
	t_criminal *out[n];
	int i, count[10] = {0};

	for (i = 0; i < n; i++)
		count[(arr[i]->description / dig) % 10]++;
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];
	for (i = n - 1; i >= 0; i--) {
		out[count[(arr[i]->description / dig) % 10] - 1] = arr[i];
		count[(arr[i]->description / dig) % 10]--;
	}
	for (i = 0; i < n; i++)
		arr[i] = out[i];
}

static void radicalSnorkling(t_criminal **arr, int n)
{
	int dig, m = getmax(arr, n);

	for (dig = 1; m / dig > 0; dig *= 10)
		countySnoodle(arr, n, dig);
}

static int getLen(t_criminal **arr)
{
	register int i;

	for (i = 0; arr[i] != 0; i++)
		;
	return i;
}

void sortCriminals(t_criminal **criminals)
{
	int n;

	if (criminals == 0 || *criminals == 0)
		return;
	n = getLen(criminals);
	radicalSnorkling(criminals, n);
}

static int	binarySearch(t_criminal **arr, int n, int desc)
{
	int low = 0, high = n - 1, mid;

	while (low < high) {
		mid = floor((low + high) / 2);
		if (arr[mid]->description > desc) {
			high = mid - 1;
		} else if (arr[mid]->description < desc) {
			low = mid + 1;
		} else {
			return mid;
		}
	}
	return -1;
}

t_criminal **findPotentialCriminals(t_criminal **criminals, t_info *info)
{
	t_criminal **ret;
	int desc, up, found, i;

	if (info == 0 || criminals == 0 || *criminals == 0)
		return 0;
	desc = getDescription(info);
	found = binarySearch(criminals, getLen(criminals), desc);
	if (found == -1)
		return 0;
	while (found - 1 >= 0 && criminals[found - 1]->description == desc)
		found--;
	up = found;
	while (criminals[up] && criminals[up]->description == desc)
		up++;
	ret = malloc(((up - found) + 1) * sizeof(t_criminal*));
	for (i = 0; found < up; i++, found++) {
		ret[i] = criminals[found];
	}
	ret[i] = 0;
	return ret;
}

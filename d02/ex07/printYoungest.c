#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "header.h"

/* Quicksort is a 'divide and conquer' algorithm */
static void	quack_swack(int *arr, int len)
{
	register int i, j, piv, tmp;

	if (len < 2 || arr == 0 || *arr == 0)
		return;

	piv = arr[len / 2];
	for (i = 0, j = len - 1; ; i++, j--) {

		while (arr[i] < piv)
			i++;

		while (arr[j] > piv)
			j--;

		if (i >= j)
			break;

		tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}
	quack_sort(arr, i);
	quack_sort(arr + i, len - i);
}

void printYoungest(int *ages, int length)
{
	if (ages == 0 || length <= 0)
		return;
	quack_swack(ages, length);
	printf("Youngest : %d\n", *ages);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

/* Arbitrary decisions:
 * highest score in input file is 100000, so maximum number of
 * 'swap' files will be 6 */

static int readBlock(FILE *f, int *arr, int size) {
	int i = 0;

	while(i < size && fscanf(f, "%d", &(arr[i])) > 0) {
		i++;
	}
	return (i);
}

static void writeFile(FILE *f, int *arr, int n) {
	register int i;

	for (i = 0; i < n; i++) {
		fprintf(f, "%d\n", arr[i]);
	}
}

static int countDigits(int n)
{
	register int i, d;

	i = d = 1;
	while (n / d) {
		d *= 10;
		i++;
	}
	return i;
}

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

void externalSort(char *scoreFile, char *sortedFile, int ram)
{
	FILE *onetwo, *threefour, *fivesix, *score;
	int *mem, tmp, i;

	if (scoreFile == 0 || sortedFile == 0 || ram <= 1)
		return;
	mem = calloc(ram, sizeof(int));
	score = fopen(scoreFile, "r");
	onetwo = fopen("onetwo.swap", "w");
	threefour = fopen("threefour.swap", "w");
	fivesix = fopen("fivesix.swap", "w");
	if (mem == 0 || score == 0 || onetwo == 0 || threefour == 0 || fivesix == 0)
		return;
	while ((tmp = readBlock(score, mem, ram)) > 0) {
		quack_swack(mem, tmp);
		for (i = 0; i < tmp; i++) {
			switch (countDigits(mem[i])) {
				case 1: case 2: fprintf(onetwo, "%d\n", mem[i]); break;
				case 3: case 4: fprintf(threefour, "%d\n", mem[i]); break;
				case 5: case 6: fprintf(fivesix, "%d\n", mem[i]); break;
			}
		}
	}
}

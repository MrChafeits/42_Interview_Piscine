#include "header.h"

void countSort(unsigned char *utensils, int n)
{
	if (utensils == 0 || *utensils == 0 || n <= 1)
		return;
	unsigned char out[n];
	int count[256] = {0}, i;

	for (i = 0; i < n; i++)
		count[(int)utensils[i]]++;
	for (i = 1; i <= 256; i++)
		count[i] += count[i - 1];
	for (i = n - 1; i >= 0; i--) {
		out[count[(int)utensils[i]] - 1] = utensils[i];
		count[(int)utensils[i]]--;
	}
	for (i = 0; i < n; i++)
		utensils[i] = out[i];
}

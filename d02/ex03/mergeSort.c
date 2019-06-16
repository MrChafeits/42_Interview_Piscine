#include <stdint.h>
#include <stdlib.h>
#include "header.h"

typedef struct s_player t_player;
/*
struct s_player {
	int score;
	char *name;
	char *timestamp;
};
*/

static uint32_t arrLen(t_player **arr)
{
	register uint32_t i;

	for (i = 0; arr[i] != 0; ++i)
		;
	return i;
}

static void mush(t_player **arr, uint32_t lo, uint32_t mid, uint32_t hi)
{
	uint32_t lsize = mid - lo + 1;
	uint32_t rsize = hi - mid;
	uint32_t i,j,k;
	t_player *left[lsize], *right[rsize];

	for (i = 0; i < lsize; i++)
		left[i] = arr[lo + i];

	for (j = 0; j < rsize; j++)
		right[j] = arr[mid + 1 + j];

	i = j = 0;
	k = lo;
	while (i < lsize && j < rsize) {

		if (left[i]->score >= right[j]->score) {
			arr[k] = left[i];
			i++;
		} else {
			arr[k] = right[j];
			j++;
		}
		k++;
	}

	while (i < lsize) {
		arr[k] = left[i];
		i++;
		k++;
	}

	while (j < rsize) {
		arr[k] = right[j];
		j++;
		k++;
	}
}

static void mangle(t_player **arr, uint32_t lo, uint32_t hi)
{
	uint32_t mid;

	mid = lo + (hi - lo) / 2;
	if (l < r) {
		mangle(arr, lo, mid);
		mangle(arr, mid + 1, hi);
		mush(arr, lo, mid, hi);
	}
}

t_player **mergeSort(t_player **players)
{
	if (players == 0 || *players == 0)
		return 0;
	mangle(players, 0, arrLen(players) - 1);
	return players;
}

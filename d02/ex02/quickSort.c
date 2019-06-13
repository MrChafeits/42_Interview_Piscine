#include "header.h"

typedef struct s_player t_player;

static int	length(t_player **arr)
{
	register int i;

	if (arr == 0 || *arr == 0)
		return 0;

	for (i = 0; arr[i] != 0; i++)
		;
	return i;
}

int partition(t_player **arr, int lo, int hi) {
	register t_player *piv, *tmp = 0;
	register int i, j;

	piv = arr[lo + (hi - lo) / 2];
	i = lo - 1;
	j = hi + 1;
	for (;;) {
		do {
			i++;
		} while (arr[i]->score > piv->score);
		do {
			j--;
		} while (arr[j]->score < piv->score);
		if (i >= j)
			return j;
		tmp = arr[j];
		arr[j] = arr[i];
		arr[i] = tmp;
	}
}

void quick_sort(t_player **arr, int lo, int hi) {
	register int p;

	if (lo < hi) {
		p = partition(arr, lo, hi);
		quick_sort(arr, lo, p);
		quick_sort(arr, p + 1, hi);
	}
}

void sortarr(t_player **arr) {
	register int lo, hi;
	if (arr == 0 || *arr == 0)
		return;
	lo = 0;
	hi = length(arr) - 1;
	quick_sort(arr, lo, hi);
}
/* Quicksort, using Hoare's partition method */

static void	quack_sort(t_player **arr, int len)
{
	register t_player *piv, *tmp;
	register int i, j;

	if (len < 2 || arr == 0 || *arr == 0)
		return;

	piv = arr[len / 2];
	for (i = 0, j = len - 1; ; i++, j--) {

		while (arr[i]->score > piv->score)
			i++;

		while (arr[j]->score < piv->score)
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

void		quickSort(t_player **players)
{
	if (players == 0 || *players == 0)
		return;

	quack_sort(players, length(players));
}

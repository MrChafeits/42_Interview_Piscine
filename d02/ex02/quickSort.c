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

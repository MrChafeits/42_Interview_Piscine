#include "header.h"

/*struct s_player {
	int   score;
	char  *name;
};*/
typedef struct s_player t_player;

void insertionSort(t_player **players)
{
	register t_player *key;
	register int i, j;

	if (players == 0 || *players == 0)
		return;
	for (i = 1; players[i] != 0; i++) {
		key = players[i];
		j = i - 1;
		while (j >= 0 && players[j]->score < key->score) {
			players[j + 1] = players[j];
			j = j - 1;
		}
		players[j + 1] = key;
	}
}

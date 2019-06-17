#include <stdio.h>
#include "header.h"

typedef struct s_bit t_bit;

/* printf("Usage: ./correctSong song.piano row col dist\n"); */
void correctSong(t_bit *bit, int l, int row, int col, int dist)
{
  printf("bit->l(%d) l(%d) row(%d) col(%d) dist(%d)\n", bit->n, l, row, col, dist);
  if (!bit || l < 0 || row < 0 || col < 0 || dist < 0 || dist + row > bit->n)
    return;
  while (dist--)
    bit->arr[row++] = (1 << col);
}

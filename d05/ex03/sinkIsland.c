#include "header.h"

void sinkIsland(int **map, int row, int col)
{
  if (map && map[row] != 0 && map[row][col] == 1) {
    map[row][col] = 0;
    if (row - 1 >= 0)
      sinkIsland(map, row - 1, col);
    if (map[row + 1] != 0)
      sinkIsland(map, row + 1, col);
    if (col - 1 >= 0)
      sinkIsland(map, row, col - 1);
    if (map[row][col + 1] != -1)
      sinkIsland(map, row, col + 1);
  }
}

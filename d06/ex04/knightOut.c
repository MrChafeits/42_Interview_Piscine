#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int getInitialPos(uint64_t board)
{
  int ret=0;
  if ((board & (board - 1)))
    return -1;
  for (uint64_t i=1;
       !(i & board);
       i<<=1,ret++);
  return ret;
}

int dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
int dy[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int max(int a, int b) { return a > b ? a : b; }
double findProb(int start_x, int start_y, int steps)
{
  /* double dp1[8][8][steps]; */
  double ***dp2;
  register int i,j,x,y,s;

  s = max(steps, 8);
  puts("alloc start");
  dp2 = malloc(9 * sizeof(double*));
  if (!dp2) return -1;
  for (i = 0; i < 8; ++i) {
    /* printf("dp2[%d] = new[8] double*\n", i); */
    dp2[i] = malloc(9 * sizeof(double*));
    if (!dp2[i]) return -1;
    for (j = 0; j < s; ++j) {
      /* printf("\tdp2[%d][%d] = new[%d] double*\n", i,j,s); */
      dp2[i][j] = calloc((steps + 1), sizeof(double));
      if (!dp2[i][j]) return -1;
    }
  }
  dp2[8] = 0;
  puts("alloc done");
  for (i = 0; i < 8; ++i)
    for (j = 0; j < 8; ++j)
      dp2[i][j][0] = 1;
  puts("init done");
  for (s = 1; s <= steps; ++s)
    {
      for (x = 0; x < 8; ++x)
        {
          for (y = 0; y < 8; ++y)
            {
              double p=0;
              for (i = 0; i < 8; ++i)
                {
                  int nx = x + dx[i];
                  int ny = y + dy[i];
                  if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8)
                    p += dp2[nx][ny][s-1] / 8.0;
                }
              printf("x(%d) y(%d) s(%d) p(%f)\n", x,y,s,p);
              dp2[x][y][s] = p;
            }
        }
    }
  puts("calc done");
  return 1.0 - dp2[start_x][start_y][steps];
}

double knightOut(uint64_t board, int n)
{
  int pos = getInitialPos(board);

  if (pos < 0 || n < 0)
    return -1;
  return findProb(pos/8,pos%8,n);
}

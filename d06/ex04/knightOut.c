#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int getInitialPos(uint64_t board)
{
	uint64_t i;
	int ret;

	if ((board & (board - 1)))
		return -1;
	ret = 0;
	for (i = 1; !(i & board); i <<= 1)
		ret++;
	return ret;
}

int max(int a, int b) { return a > b ? a : b; }

double findProb(int start_x, int start_y, int steps)
{
	static int dx[8] = {1, 2, 2, 1,-1,-2,-2,-1};
	static int dy[8] = {2, 1,-1,-2,-2,-1, 1, 2};
	double dp2[8][8][steps+1];
	int i,j,x,y,s,nx,ny;

	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			dp2[i][j][0] = 1;
	for (s = 1; s <= steps; s++) {
		for (x = 0; x < 8; x++) {
			for (y = 0; y < 8; y++) {
				double p=0;
				for (i = 0; i < 8; i++) {
					nx = x + dx[i];
					ny = y + dy[i];
					if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8)
						p += dp2[nx][ny][s-1] / 8.0;
				}
				dp2[x][y][s] = p;
			}
		}
	}
	return 1.0 - dp2[start_x][start_y][steps];
}

/* Bruteforcing all positions on the board shows that for 85 moves or more,
   the probability is always 1.0 */

double knightOut(uint64_t board, int n)
{
	int pos = getInitialPos(board);

	if (pos < 0 || n < 0)
		return -1;
	if (n >= 85)
		return 1.0;
	return findProb(pos / 8, pos % 8, n);
}

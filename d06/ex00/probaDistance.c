#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

void combUtil(int *loc, int n, int r, int idx, int tmp[], int i, int dist, int *total, int *good)
{
  if (idx == r) {
    *total = *total + 1;
    if (abs(tmp[0] - tmp[1]) > dist)
      *good = *good + 1;
    return;
  }
  if (i >= n)
    return;
  tmp[idx] = loc[i];
  combUtil(loc, n, r, idx+1, tmp, i+1, dist, total, good);
  combUtil(loc, n, r, idx, tmp, i+1, dist, total, good);
}

double probaDistance(int dist, int *locations, int n)
{
  int hhh[2], total=0, good=0;

  if (!locations)
    return nan(0);
  combUtil(locations, n, 2, 0, hhh, 0, dist, &total, &good);
  printf("[DBG: good(%d) total(%d)]\n", good,total);
  return (double)good / (double)total;
}

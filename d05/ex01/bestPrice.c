#include "header.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

double findPermsRecur(int *arr, int idx, int num, int rnum, double *prices, double cur, double tmp)
{
  if (rnum < 0)
    return cur;
  if (rnum == 0) {
    int i = -1;
    while (++i < idx)
      tmp += prices[arr[i]];
    return fmax(cur, tmp);
  }
  int prev = (idx == 0 ? 1 : arr[idx - 1]) - 1;
  while (++prev < num + 1) {
    arr[idx] = prev;
    cur = fmax(findPermsRecur(arr, idx + 1, num, rnum - prev, prices, cur, 0), cur);}
  return cur;
}

double bestPrice(int pizzaSize, double *prices)
{
  if (pizzaSize <= 0)
    return 0;
  int arr[pizzaSize];
  bzero(arr, sizeof(arr));
  double ret = findPermsRecur(arr, 0, pizzaSize, pizzaSize, prices, 0, 0);
  return ret;
}

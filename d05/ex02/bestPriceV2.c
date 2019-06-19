#include "header.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

double find(int n, double *arr, double *prices, int end)
{
  double max = 0, ret = 0;
  int i = 0;

  if (arr[n])
    return arr[n];
  while (i++ < n) {
    ret = find(n - i, arr, prices, 0);
    max = fmax(ret + prices[i], max);
  }
  arr[n] = max;
  if (end)
    free(arr);
  return max;
}

double optimizedBestPrice(int pizzaSize, double *prices)
{
  return find(pizzaSize, calloc(pizzaSize + 1, sizeof(double)), prices, 1);
}


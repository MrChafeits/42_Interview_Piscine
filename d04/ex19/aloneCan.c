#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void aloneCan(int *arr, int n)
{
  register int ret, i;

  if (!arr)
    return;
  for (i = ret = 0; i < n; i++)
    ret ^= arr[i];
  printf("%d\n", ret);
}

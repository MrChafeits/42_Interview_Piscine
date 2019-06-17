#include <stdio.h>
#include "header.h"

void aloneCans(int *arr, int n)
{
  register int ret, i, a, b, x;

  if (arr) {
    for (i = ret = a = b = x = 0; i < n; i++)
      x ^= arr[i];
    ret = x & ~(x-1);
    for (i = 0; i < n; i++) {
      if (arr[i] & ret)
        a ^= arr[i];
      else
        b ^= arr[i];
    }
    printf("%d\n%d\n", a, b);
  }
}

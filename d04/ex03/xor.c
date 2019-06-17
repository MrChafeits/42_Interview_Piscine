#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "header.h"

char *getXor(char *a, char *b)
{
  int i;

  if (!a || !b) {
    if (a)
      return a;
    else if (b)
      return b;
    else
      return 0;
  }
  for (i = 5; i >= 0; i--) {
    a[i] = (a[i] != b[i]) + '0';
  }
  return a;
}

int toInt(char *bits)
{
  if (!bits)
    return 0;
  return strtol(bits, 0, 2);
}

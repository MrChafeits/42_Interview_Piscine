#include <string.h>
#include <stdio.h>
#include "header.h"

void swap(char *a, char *b)
{
  char tmp = *a;
  *a = *b;
  *b = tmp;
}

void permute(char *s, int l, int r)
{
  int i;
  if (l == r)
    puts(s);
  else {
    i = l - 1;
    while (++i <= r) {
      swap((s+l), (s+i));
      permute(s, l+1, r);
      swap((s+l), (s+i));
    }
  }
}

void printPermutations(char *str)
{
  permute(str, 0, strlen(str) - 1);
}

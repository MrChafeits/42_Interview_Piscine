#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void getNot(char *a)//TODO: fix this
{
  int i;

  if (!a || *a != '~')
    return;
  for (i = 0; a[i+1] != 0; i++)
    a[i] = '0' + !(a[i+1] - '0');
  a[i] = 0;
}

char *getAnd(char *a, char *b)
{
  char *ret;
  int i;

  if (!a || !b) {
    if (!a && b)
      return a;
    else if (a && !b)
      return b;
    else
      return 0;
  }
  getNot(a);
  getNot(b);
  ret = calloc(5, sizeof(*a));
  for (i = strlen(a); i >= 0; i--) {
    ret[i] = '0' + (a[i] == b[i] && a[i] == '1');
  }
  return ret;
}

char *getOr(char *a, char *b)
{
  char *ret;
  int i;

  if (!a || !b) {
    if (!a && b)
      return a;
    else if (a && !b)
      return b;
    else
      return 0;
  }
  getNot(a);
  getNot(b);
  ret = calloc(5, sizeof(*a));
  for (i = 3; i >= 0; i--) {
    ret[i] = '0' + (a[i] == '1' || b[i] == '1');
  }
  return ret;
}

int toInt(char *bits)
{
  if (!bits)
    return 0;
  char *endptr = strchr(bits, 0);
  return strtol(bits, &endptr, 2);
}

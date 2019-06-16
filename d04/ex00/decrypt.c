#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

char *getSum(char *a, char *b)
{
  if (!a || !b) {
    if (!a && b)
      return b;
    else if (a && !b)
      return a;
    else
      return 0;
  }
  int carry = 0, i;
  for (i = 5; i >= 0; i--) {
    if (carry == 1) {
      if (a[i] != b[i]) {
        if (a[i] == '0')
          a[i] = '1';
        else
          b[i] = '1';
        carry = 0;
      } else {
        if (a[i] == '1') {
          carry = 1;
          a[i] = '0';
        } else {
          carry = 0;
          a[i] = '1';
        }
      }
    }
    if (a[i] == b[i] && b[i] == '0') {
      a[i] = '0';
    } else if (a[i] != b[i]) {
      a[i] = '1';
    } else if (a[i] == b[i] && b[i] == '1') {
      a[i] = '0';
      carry = 1;
    }
  }
  return a;
}

int toInt(char *bits)
{
  if (!bits)
    return 0;
  char *endptr = strchr(bits, 0);
  return strtol(bits, &endptr, 2);
}

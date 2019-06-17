#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1

char *getSum(char *a, char *b)
{
  char tmp[6] = {0};
  int carry = 0, i, aa, bb;

  for (i = 5; i >= 0; i--) {
    aa = a[i];
    bb = b[i];
    tmp[i] = (aa ^ bb ^ carry) + '0';
    carry = ((aa - '0') & (bb - '0'))
      | ((bb - '0') & carry)
      | ((aa - '0') & carry);
  }
  for (i = 0; i < 6; i++)
    a[i] = tmp[i];
  return a;
}

#else

char *getSum(char *a, char *b)
{
  int carry, i;

  if (!a || !b) {
    if (b)
      return b;
    else if (a)
      return a;
    else
      return 0;
  }
  carry = 0;
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
    if (a[i] == b[i]) {
      a[i] = '0';
      if (b[i] == '1')
        carry = 1;
    } else {
      a[i] = '1';
    }
  }
  return a;
}

#endif

int toInt(char *bits)
{
  if (!bits)
    return 0;
  return strtol(bits, 0, 2);
}

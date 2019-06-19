#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "header.h"

char *rightShift(char *bin, int k)
{
  char tmp[6] = {0};
  int i, se = 0;

  if (k <= 0)
    return strdup(bin);
  if (k >= 6)
    return strdup(bin[0] == '1' ? "111111" : "000000");
  if (bin != 0) {
    se = (bin[0] == '1');
    while (k--) {
      for (i = 0; i < 6; i++) {
        if (i == 0) {
          if (bin[i] == '1') {
            tmp[i] = bin[i];
          } else {
            tmp[i] = '0';
          }
          tmp[i+1] = bin[i];
        } else {
          if (i + 1 < 6)
            tmp[i+1] = bin[i];
        }
      }
      for (i = 0; i < 6; i++)
        bin[i] = tmp[i];
    }
  }
  return bin;
}

char *leftShift(char *bin, int k)
{
  char tmp[6] = {0};
  int i;

  if (k <= 0)
    return strdup(bin);
  if (k >= 6)
    return strdup("000000");
  if (bin != 0) {
    while (k--) {
      for (i = 5; i >= 0; i--) {
        if (i == 5) {
          tmp[i] = '0';
          tmp[i-1] = bin[i];
        } else {
          if (i - 1 >= 0)
            tmp[i-1] = bin[i];
        }
      }
      for (i = 0; i < 6; i++)
        bin[i] = tmp[i];
    }
  }
  return bin;
}

static char *twosComp(char *bin)
{
  char *res;
  int i, k, n = 6;

  res = strdup(bin);
  for (i = n - 1; i >= 0; i--)
    if (res[i] == '1')
      break;
  if (i == -1) {
    res[0] = '1';
    return res;
  }
  for (k = i - 1; k >= 0; k--) {
    if (res[k] == '1')
      res[k] = '0';
    else
      res[k] = '1';
  }
  return res;
}

int toInt(char *bits)
{
  if (!bits)
    return 0;
  if (bits[0] == '1')
    return -(strtol(twosComp(bits), 0, 2));
  else
    return strtol(bits, 0, 2);
}

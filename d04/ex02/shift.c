#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "header.h"

char *rightShift(char *bin, int k)
{
  char tmp[6] = {0};
  int i;

  if (bin != 0) {
    while (k--) {
      for (i = 0; i < 6; i++) {
        if (i == 0) {
          tmp[i] = '0';
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

int toInt(char *bits)
{
  if (!bits)
    return 0;
  char *endptr = strchr(bits, 0);
  return strtol(bits, &endptr, 2);
}

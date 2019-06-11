#include "header.h"
#include <string.h>
#include <unistd.h>

/* Rabin-Karp string search algorithm using a simple string sum
 * "hash" */

int sumstr(char *str, int start, int end) {
  int i, total = 0;

  for (i = start; i <= end; i++)
    total += str[i];
  return total;
}
int howManyJesus(char *bible, char *jesus) {
  int total = 0;
  int jlen = strlen(jesus);
  int jsum = sumstr(jesus, 0, jlen - 1);
  int cur = 0, l = 0, r = 0;

  while (bible[r] && r < jlen) {
    cur += bible[r];
    r++;
  }
  for (r = r - 1; bible[r] != 0;) {
    if (jsum == cur) {
      if (strncmp(jesus, bible + l, jlen) == 0)
        total++;
      l++;
      r++;
    } else {
      l++;
      r++;
      cur -= bible[l - 1];
      cur += bible[r];
    }
  }
  return total;
}

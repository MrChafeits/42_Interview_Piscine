#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isPalindrome(char *str)
{
  size_t i, l = strlen(str) / 2, tmp;

  i = tmp = 0;
  while (i < l)
    tmp += str[i++];
  i = l;
  while (str[i])
    tmp -= str[i++];
  return !tmp;
}

int maxxy(int a, int b) { return a > b ? a : b; }

char *findPalindrome(char *sequence, int nDelete)
{
  (void)nDelete;
  int i, j, n=strlen(sequence), L[n][n];
  for (i = 0; i < n; i++)
    L[i][i] = 1;
  for (int cl = 2; cl <= n; cl++) {
    for (i = 0; i < n - cl + 1; i++) {
      j = i + cl - 1;
      if (sequence[i] == sequence[j] && cl == 2) {
        fprintf(stderr, "[DBG: two sequence(%*s)]\n", cl, sequence);
        L[i][j] = 2;
        fprintf(stderr, "[DBG: two L[%d][%d](%d)]\n", i, j, L[i][j]);
      } else if (sequence[i] == sequence[j]) {
        fprintf(stderr, "[DBG: mid sequence(%*s)]\n", i, sequence);
        L[i][j] = L[i+1][j-1] + 2;
        fprintf(stderr, "[DBG: mid L[%d][%d](%d)]\n", i, j, L[i][j]);
      } else {
        fprintf(stderr, "[DBG: max sequence(%*s)]\n", cl, sequence);
        L[i][j] = maxxy(L[i][j-1],L[i+1][j]);
        fprintf(stderr, "[DBG: max L[%d][%d](%d)]\n", i, j, L[i][j]);
      }
    }
  }
  fprintf(stderr, "[DBG: end L[0][%d](%d)]\n", n-1, L[0][n-1]);
  return sequence;
}

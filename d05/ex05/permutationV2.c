#include "header.h"
#include <stdio.h>
#include <string.h>

typedef struct s_dict t_dict;
typedef struct s_item t_item;

void swap(char *a, char *b)
{
  char tmp = *a;
  *a = *b;
  *b = tmp;
}

void permute(t_dict *d, char *s, int l, int r)
{
  int i;
  if (l == r && dictSearch(d, s) == -1) {
    dictInsert(d, s, 1);
    puts(s);
  } else {
    i = l - 1;
    while (++i <= r) {
      swap((s+l), (s+i));
      permute(d, s, l+1, r);
      swap((s+l), (s+i));
    }
  }
}

void printUniquePermutations(char *str)
{
  t_dict *d;
  size_t l = strlen(str), r=1, i=0;
  while (i < l)
    r *= (l - i++);
  fprintf(stderr, "r(%zu)\n", r);
  d = dictInit(r);
  permute(d, str, 0, l - 1);
}

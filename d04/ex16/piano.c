#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

typedef struct s_bit t_bit;
#if 0
struct s_bit {
	int *arr;
	int n;
};
#endif

int	**pianoDecompress(t_bit *bit, int l)
{
  int **ret = 0, i, j;

  if (!bit || l <= 0)
    goto end;
  ret = calloc(bit->n + 1, sizeof(*ret));
  if (!ret)
    goto end;
  for (i = 0; i < bit->n; i++) {
    ret[i] = calloc(l, sizeof(int));
    if (!ret[i])
      goto end;
  }
  for (i = 0; i < bit->n; i++) {
    for (j = 0; j < l; j++) {
      ret[i][j] = (bit->arr[i] & 1);
      bit->arr[i] >>= 1;
    }
  }
 end:
  return ret;
}

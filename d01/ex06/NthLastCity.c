#include "header.h"

typedef struct s_city t_city;

void traverse(t_city *city, int n, int *depth, char **res) {
  if (city == 0)
    return;
  traverse(city->next, n, depth, res);
  *depth = *depth + 1;
  if (*depth == n + 1)
    *res = city->name;
}

char *NthLastCity(t_city *city, int n) {
  char *res = 0;
  int depth = 0;

  if (city == 0 || n < 0)
    return 0;
  traverse(city, n, &depth, &res);
  return res;
}

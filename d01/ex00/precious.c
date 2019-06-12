#include "header.h"
#include <stdlib.h>
#include <string.h>

t_node *node_create(char c) {
  t_node *new;

  new = malloc(sizeof(*new));
  if (new == 0)
    return 0;
  new->c = c;
  new->prev = new->next = new;
  return new;
}

t_node *construct_ring(void) {
  t_node *ring = 0, *tmp = 0, *last = 0;
  const char *str = CS;
  int i = 0, len = 0;

  len = strlen(str);
  for (i = 0; i < len; i++) {
    tmp = node_create(str[i]);
    if (ring == 0) {
      ring = tmp;
    } else {
      last = ring->prev;
      tmp->next = ring;
      ring->prev = tmp;
      tmp->prev = last;
      last->next = tmp;
    }
  }
  return ring;
}

t_node *swooce(t_node *n, int offset) {
  if (offset > 0) {
    while (offset--)
      n = n->next;
  } else if (offset < 0) {
    while (offset++)
      n = n->prev;
  }
  return n;
}

char *precious(int *text, int size) {
  t_node *ring;
  char *res;
  int i;

  res = malloc((size + 1) * sizeof(*res));
  ring = construct_ring();
  for (i = 0; i < size; i++) {
    ring = swooce(ring, text[i]);
    res[i] = ring->c;
  }
  res[i] = 0;
  return res;
}

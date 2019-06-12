#include "header.h"
#include <stdlib.h>

typedef struct s_node t_node;

t_node *newNode(int val) {
  t_node *new;

  new = malloc(sizeof(*new));
  if (new == 0)
    return 0;
  new->value = val;
  new->random = new->next;
  return new;
}

t_node *cloneGameBoard(t_node *node) {
  t_node *ret, *tmp, *new;

  if (node == 0)
    return 0;
  ret = newNode(node->value);
  ret->random = node;
  tmp = node->next;
  ret->next = node->next;
  node->next = ret;
  while (tmp) {
    new = newNode(tmp->value);
    new->random = tmp;
    tmp = tmp->next;
    new->next = new->random->next;
    new->random->next = new;
  }
  tmp = ret;
  while (tmp) {
    if (tmp->random->random)
      tmp->random = tmp->random->random->next;
    else
      tmp->random = 0;
    if (tmp->next)
      tmp = tmp->next->next;
    else
      tmp = 0;
  }
  tmp = ret;
  while (node) {
    if (node->next)
      node->next = node->next->next;
    node = node->next;
    if (tmp->next)
      tmp->next = tmp->next->next;
    tmp = tmp->next;
  }
  return ret;
}

#include "header.h"
#include <stdio.h>

typedef struct s_node t_node;

static void printReverse_internal(t_node *lst) {
  if (lst == 0)
    return;
  if (lst->next)
    printReverse_internal(lst->next);
  if (lst->next == 0)
    printf("%s", lst->word);
  else
    printf(" %s", lst->word);
}

void printReverse(t_node *lst) {
  printReverse_internal(lst);
  printf("\n");
}

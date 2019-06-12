#include "header.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_node t_node;
typedef struct s_item t_item;
typedef struct s_stack t_stack;

t_stack *stackInit(void) {
  t_stack *new;

  new = malloc(sizeof(*new));
  if (new != 0)
    new->item = 0;
  return new;
}

void *pop(t_stack *stack) {
  t_item *tmp;
  char *ret;

  if (stack == 0 || stack->item == 0)
    return 0;
  tmp = stack->item;
  stack->item = stack->item->next;
  ret = tmp->word;
  free(tmp);
  return ret;
}

void push(t_stack *stack, char *word) {
  t_item *new;

  if (stack == 0)
    return;
  new = malloc(sizeof(*new));
  if (new != 0) {
    new->word = word;
    new->next = stack->item;
    stack->item = new;
  }
}

void printReverseV2(t_node *lst) {
  t_stack *st;
  t_node *t1;
  int goodProgrammingStyleFlag;

  st = stackInit();
  for (t1 = lst; t1 != 0; t1 = t1->next)
    push(st, t1->word);
  goodProgrammingStyleFlag = 0;
  while (st->item) {
    if (goodProgrammingStyleFlag == 0) {
      printf("%s", pop(st));
      goodProgrammingStyleFlag = 1;
    } else {
      printf(" %s", pop(st));
    }
  }
  printf("\n");
}

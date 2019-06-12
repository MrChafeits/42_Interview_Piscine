#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_item t_item;
typedef struct s_stack t_stack;

t_stack *initStack(void) {
  t_stack *new;

  new = malloc(sizeof(*new));
  if (new != 0)
    new->item = 0;
  return new;
}

int pop(t_stack *stack) {
  t_item *tmp;
  int ret;

  if (stack == 0 || stack->item == 0)
    return 0;
  tmp = stack->item;
  stack->item = stack->item->next;
  ret = tmp->idx;
  free(tmp);
  return ret;
}

void push(t_stack *stack, int idx) {
  t_item *new;

  if (stack == 0)
    return;
  new = malloc(sizeof(*new));
  if (new != 0) {
    new->idx = idx;
    new->next = stack->item;
    stack->item = new;
  }
}

char *console(void) {
  t_stack *st;
  char buf[256] = {0};
  char *tmp = 0;
  size_t tmpcap = 0;
  int idx, i, br;

  st = initStack();
  idx = i = 0;
  br = 1;
  printf("MSG> ");
  while ((br = getline(&tmp, &tmpcap, stdin)) > 0) {
    if (strcmp("UNDO\n", tmp) == 0) {
      i = pop(st);
      bzero(buf + (idx - i), i);
      idx -= i;
    } else if (strcmp("SEND\n", tmp) == 0) {
      goto end;
    } else {
      if (br + idx <= 256) {
        strncpy(buf + idx, tmp, br - 1);
        idx += br - 1;
        push(st, br - 1);
      } else {
        puts("ERROR: Input exceeds 255 bytes in length, discarding...");
      }
    }
    puts(buf);
    printf("MSG> ");
  }
end:
  free(tmp);
  while (pop(st))
    ;
  free(st);
  return strdup(buf);
}

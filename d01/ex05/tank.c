#include "header.h"
#include <stdlib.h>

#define MAX_TANKS 64

typedef struct s_elem t_elem;
typedef struct s_stack t_stack;
typedef struct s_tank t_tank;

t_tank *initTank(void) {
  t_tank *new;
  int i;

  new = malloc(sizeof(*new));
  if (new != 0) {
    new->n = 1;
    new->stacks = malloc((MAX_TANKS + 1) * sizeof(t_stack *));
    if (new->stacks != 0) {
      for (i = 0; i <= MAX_TANKS; i++)
        new->stacks[i] = 0;
      new->stacks[0] = malloc(sizeof(t_stack));
      if (new->stacks[0] != 0) {
        new->stacks[0]->elem = 0;
        new->stacks[0]->sum = 0;
      }
    } else {
      free(new);
      new = 0;
    }
  }
  return new;
}

void tankPush(t_tank *tank, int energy) {
  t_elem *new;
  t_stack *st;

  if (tank == 0 || energy < 10 || energy > 100)
    return;
  new = malloc(sizeof(*new));
  if (new != 0) {
    new->energy = energy;
    new->next = 0;
    if (tank->stacks[tank->n - 1]->sum + energy <= 1000) {
      tank->stacks[tank->n - 1]->sum += energy;
      new->next = tank->stacks[tank->n - 1]->elem;
      tank->stacks[tank->n - 1]->elem = new;
    } else if (tank->n < MAX_TANKS) {
      st = malloc(sizeof(*st));
      st->elem = new;
      st->sum = energy;
      tank->stacks[tank->n] = st;
      tank->n++;
    } else {
      free(new);
    }
  }
}

int tankPop(t_tank *tank) {
  t_elem *e;
  t_stack *st;
  int ret = 0;

  if (tank == 0 || tank->stacks == 0 || tank->n == 0)
    return 0;
  st = tank->stacks[tank->n - 1];
  if (st != 0) {
    e = st->elem;
    st->elem = e->next;
    st->sum -= e->energy;
    ret = e->energy;
    free(e);
    if (st->elem == 0) {
      tank->n--;
      free(st);
    }
  }
  return ret;
}

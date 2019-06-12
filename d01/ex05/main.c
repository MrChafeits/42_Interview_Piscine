#include <stdio.h>  //printf, scanf, ...
#include <stdlib.h> //malloc, free, exit...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...

#include "header.h"

int main(void) {
  struct s_tank *tank = initTank();
  int tmp;

  /*-------------------
  launch your test here
  --------------------*/
  tankPush(tank, 10);
  printf("push(10)\n");
  printf("tank->n(%d)\n", tank->n);
  printf("tank->stacks[%d]->sum(%d)\n", tank->n - 1,
         tank->stacks[tank->n - 1]->sum);
  tankPush(tank, 50);
  printf("push(50)\n");
  printf("tank->n(%d)\n", tank->n);
  printf("tank->stacks[%d]->sum(%d)\n", tank->n - 1,
         tank->stacks[tank->n - 1]->sum);
  tankPush(tank, 23);
  printf("push(23)\n");
  printf("tank->n(%d)\n", tank->n);
  printf("tank->stacks[%d]->sum(%d)\n", tank->n - 1,
         tank->stacks[tank->n - 1]->sum);
  tankPush(tank, 93);
  printf("push(93)\n");
  printf("tank->n(%d)\n", tank->n);
  printf("tank->stacks[%d]->sum(%d)\n", tank->n - 1,
         tank->stacks[tank->n - 1]->sum);
  tankPush(tank, 73);
  printf("push(73)\n");
  printf("tank->n(%d)\n", tank->n);
  printf("tank->stacks[%d]->sum(%d)\n", tank->n - 1,
         tank->stacks[tank->n - 1]->sum);
  tankPush(tank, 830);
  printf("push(830)\n");
  printf("tank->n(%d)\n", tank->n);
  printf("tank->stacks[%d]->sum(%d)\n", tank->n - 1,
         tank->stacks[tank->n - 1]->sum);
  tmp = tankPop(tank);
  printf("pop(%d)\n", tmp);
  printf("tank->n(%d)\n", tank->n);
  printf("tank->stacks[%d]->sum(%d)\n", tank->n - 1,
         tank->stacks[tank->n - 1]->sum);
  tmp = tankPop(tank);
  printf("pop(%d)\n", tmp);
  printf("tank->n(%d)\n", tank->n);
  printf("tank->stacks[%d]->sum(%d)\n", tank->n - 1,
         tank->stacks[tank->n - 1]->sum);
  tmp = tankPop(tank);
  printf("pop(%d)\n", tmp);
  printf("tank->n(%d)\n", tank->n);
  printf("tank->stacks[%d]->sum(%d)\n", tank->n - 1,
         tank->stacks[tank->n - 1]->sum);
  tmp = tankPop(tank);
  printf("pop(%d)\n", tmp);
  printf("tank->n(%d)\n", tank->n);
  printf("tank->stacks[%d]->sum(%d)\n", tank->n - 1,
         tank->stacks[tank->n - 1]->sum);
  tmp = tankPop(tank);
  printf("pop(%d)\n", tmp);
  printf("tank->n(%d)\n", tank->n);
  printf("tank->stacks[%d]->sum(%d)\n", tank->n - 1,
         tank->stacks[tank->n - 1]->sum);
  tmp = tankPop(tank);
  printf("pop(%d)\n", tmp);
  printf("tank->n(%d)\n", tank->n);
  return (0);
}

// Function used for the test
// Don't go further :)

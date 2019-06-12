#include <stdio.h>  //printf, scanf, ...
#include <stdlib.h> //malloc, free, exit...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...

#include "header.h"

int main(void) {

  /*-------------------
  launch your test here
  --------------------*/
  char *msg1 = "aaa";
  char *msg2 = "bbb";
  char *msg3 = "ccc";
  struct s_queue *q;
  q = queueInit();
  printf("isEmpty(%d) peek(%s)\n", isEmpty(q), peek(q));
  enqueue(q, msg1);
  printf("enqueue msg1\n");
  printf("isEmpty(%d) peek(%s)\n", isEmpty(q), peek(q));
  enqueue(q, msg2);
  printf("enqueue msg2\n");
  printf("isEmpty(%d) peek(%s)\n", isEmpty(q), peek(q));
  enqueue(q, msg3);
  printf("enqueue msg3\n");
  printf("isEmpty(%d) peek(%s)\n", isEmpty(q), peek(q));
  printf("dequeue(%s)\n", dequeue(q));
  printf("isEmpty(%d) peek(%s)\n", isEmpty(q), peek(q));
  printf("dequeue(%s)\n", dequeue(q));
  printf("isEmpty(%d) peek(%s)\n", isEmpty(q), peek(q));
  printf("dequeue(%s)\n", dequeue(q));
  printf("isEmpty(%d) peek(%s)\n", isEmpty(q), peek(q));
  printf("dequeue(%s)\n", dequeue(q));
  free(q);

  return (0);
}

// Function used for the test
// Don't go further :)

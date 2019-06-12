#include <stdio.h>  //printf, scanf, ...
#include <stdlib.h> //malloc, free, exit...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...

#include "header.h"

int main(void) {
  char *msg;
  /*-------------------
  launch your test here
  --------------------*/
  msg = console();
  printf("recieved message: %s\n", msg);
  free(msg);

  return (0);
}

// Function used for the test
// Don't go further :)

#include <stdio.h> //printf, scanf, ...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...
#include <stdlib.h> //malloc, free, exit...
#include <time.h>

#include "header.h"

int main(int ac, char **av)
{
	char *word = NULL;

	if (ac >= 2){
		word = av[1];
	} else {
    printf("Usage: %s [word]\n", *av);
    return 1;
  }

	/*-------------------
	launch your test here
	--------------------*/
  clock_t start, stop;

  start = clock();
	printPermutations(word);
  stop = clock();
  printf("clocks(%lu) approx_time(%f)\n", stop-start, (double)(stop-start)/CLOCKS_PER_SEC);

	return (0);
}



// Function used for the test
// Don't go further :)


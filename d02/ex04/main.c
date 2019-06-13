#include <stdio.h> //printf, scanf, ...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...
#include <stdlib.h> //malloc, free, exit...
#include <time.h>

#include "header.h"

int main(void)
{
	unsigned char *utensils;
	int n = 0;
	clock_t start = 0, end = 0;

/* if param == 0, the length of the list will be random between 1 and 1 million */
	utensils = genRandomUstensils(&n);

	/*-------------------
	launch your test here
	--------------------*/
	printUtensils(utensils, n, 0);

	puts("sorting using count sort...");
	start = clock();
	countSort(utensils, n);
	end = clock();
	printf("clock_ticks(%lu)\n", end - start);
	printUtensils(utensils, n, 0);

	return (0);
}



// Function used for the test
// Don't go further :)

void printUtensils(unsigned char *utensils, int n, int verbose)
{
	int order = 1;
	printf("{ ");
	for (int i = 0; i < n; i++){
		if (verbose)
			printf("%d%s", utensils[i], (i + 1 < n) ? ", " : " ");
		if (i >= 1 && utensils[i - 1] > utensils[i])
			order = 0;
	}
	if (!verbose)
		printf("length: %d ", n);
	printf("} (%s)\n", (order) ? "sorted" : "not sorted");
}


#define NUMBER_OF_USTENSILS 15

unsigned char *genRandomUstensils(int *n)
{
	unsigned char *utensils;

	srand(time(NULL));
	if ((*n) <= 0 || (*n) > 1000000000){
		(*n) = rand() % 1000000 + 1; //generating int between 1 and 1.000.000
	}
	utensils = malloc(sizeof(unsigned char) * (*n));
	for (int i = 0; i < (*n); i++){
		utensils[i] = rand() % NUMBER_OF_USTENSILS + 1;
	}
	return (utensils);
}

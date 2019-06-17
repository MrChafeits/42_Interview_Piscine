#include <stdio.h> //printf, scanf, ...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...
#include <stdlib.h> //malloc, free, exit...
#include <time.h>

#include "header.h"

int main(int ac, char **av)
{
	unsigned int parkingRow;
	int res;
	clock_t start, stop;

	if (ac == 2) {
		parkingRow = atoi(av[1]);
	} else {
		printf("usage: ./occupiedPlaces parkingRow\n");
		return (0);
	}
	/*-------------------
	launch your test here
	--------------------*/
	start = clock();
	res = occupiedPlaces(parkingRow);
	stop = clock();
	printf("clocks(%lu) approx_time(%f)\n", stop-start, (double)(stop-start)/CLOCKS_PER_SEC);
	printf("Parking row %d has %d occupied places\n", parkingRow, res);

	return (0);
}



// Function used for the test
// Don't go further :)


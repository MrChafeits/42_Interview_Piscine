#include <stdio.h> //printf, scanf, ...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...
#include <stdlib.h> //malloc, free, exit...

#include "header.h"

int main(int argc, char *argv[])
{
	char *book;

	//getting the file
	book = readFile();

	/*-------------------
	launch your test here
	--------------------*/
	char *word;

	if (argc == 2)
		word = argv[1];
	else
		word = "God";
	printf("howManyJesus(book, \'%s\') = %d\n", word, howManyJesus(book, word));

	return (0);
}



// Function used for the test
// Don't go further :)

#define FILENAME "book.txt"

void	leave(void){
	dprintf(STDERR_FILENO, "failed to load the file.\n");
	exit(0);
}

char	*readFile(void)
{
	char *fcontent = NULL;
	int size = 0;
	FILE *fp;

	printf("Loading the file... ");
	if (NULL == (fp = fopen(FILENAME, "r")))
		leave();
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	if (NULL == (fcontent = malloc(sizeof(char) * (size + 1))))
		leave();
	fread(fcontent, 1, size, fp);
	fclose(fp);
	printf("finish!\n");
	return (fcontent);
}

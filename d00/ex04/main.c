#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "header.h"

#define FILENAME "book.txt"

void	panic(char *msg){
	if (msg)
		puts(msg);
	exit(EXIT_FAILURE);
}

char	*readFile(void)
{
	char *buf = NULL;
	int size = 0;
	FILE *fp;

	puts("Reading file...");
	fp = fopen(FILENAME, "r");
	if (fp == 0)
		panic("Fatal error: unable to open file");
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	buf = malloc(sizeof(char) * (size + 1));
	if (buf == 0)
		panic("Fatal error: unable to allocate space for file contents");
	fread(buf, 1, size, fp);
	fclose(fp);
	puts("Done");
	return (buf);
}

int main(int argc, char *argv[])
{
	char *book;
	char *word;

	if (argc == 2)
		word = argv[1];
	else
		word = "jesus";
	book = readFile();
	printf("Total occurrances of \'%s\': %d\n", word, howManyJesus(book, word));
	return 0;
}

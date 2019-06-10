#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "header.h"

#define FILENAME "art.txt"

char	*read_file(void)
{
	char *buf = NULL;
	FILE *fp = NULL;
	long size = 0;

	fp = fopen(FILENAME, "r");
	if (fp == NULL) return NULL;
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	buf = malloc((size + 1) * sizeof(*buf));
	if (buf == NULL) return NULL;
	fread(buf, 1, size, fp);
	fclose(fp);
	return buf;
}

char	**split(char *str, char *del)
{
	char **r = 0;
	int a = 0, pos = 0, count = 0, ldel = strlen(del), lsub = 0;
	register int i=0;

	for (i = 0; str[i]; ++i) {
		if (strncmp(str + i, del, ldel) == 0) {
			if (lsub > 0) {
				lsub = 0;
				count++;
			}
			i = i + ldel - 1;
		} else {
			lsub++;
		}
	}
	if (lsub > 0)
		count++;
	r = malloc((count + 1) * sizeof(*r));
	if (r == 0)
		return 0;
	*r = 0;
	lsub = 0;
	for (i = 0; str[i]; i++) {
		if (strncmp(str + i, del, ldel) == 0) {
			if (lsub > 0) {
				r[a] = strndup(str + pos, lsub);
				a++;
				lsub = 0;
			}
			i = i + ldel - 1;
			pos = i + 1;
		} else {
			lsub++;
		}
	}
	if (lsub > 0) {
		r[a] = strndup(str + pos, lsub);
		a++;
	}
	r[a] = NULL;
	return r;
}

t_art *init_struct(char *l)
{
	t_art *p = 0;
	char **arr = 0;
	int i;

	p = malloc(sizeof(*p));
	if (p == NULL)
		return NULL;
	arr = split(l, " => ");
	if (arr == NULL)
		return NULL;
	if (*arr != NULL)
		p->name = strdup(*arr);
	else
		return NULL;
	if (arr[1] != NULL)
		p->price = atoi(arr[1]);
	else
		return NULL;
	for (i = 0; arr[i] != NULL; i++)
		free(arr[i]);
	free(arr);
	return p;
}

void panic(const char *msg)
{
	if (msg)
		puts(msg);
	exit(EXIT_FAILURE);
}

t_art **parse_file(void)
{
	char *buf=0, **tab=0;
	t_art **arr=0, *temp=0;
	int size=0, idx=0;
	register int i=0;

	puts("loading file...");
	buf = read_file();
	if (buf == NULL)
		panic("Fatal error: failed to read file.");
	size = 0;
	for (i = 0; buf[i] != 0; i++)
		if (buf[i] == '\n')
			size++;
	arr = malloc((size + 1) * sizeof(*arr));
	if (arr == NULL)
		panic("Fatal error: failed to allocate memory for arr.");
	idx = 0;
	*arr = NULL;
	tab = split(buf, "\n");
	for (i = 0; tab[i] != NULL; i++) {
		temp = init_struct(strdup(tab[i]));
		if (temp) {
			arr[idx] = temp;
			idx++;
		}
	}
	arr[idx] = NULL;
	for (i = 0; tab[i] != NULL; i++)
		free(tab[i]);
	free(tab);
	puts("Done");
	return arr;
}

/* END BOILERPLATE FILEPARSING */

int length(struct s_art **arts)
{
	register int i;

	if (arts == 0 || *arts == 0)
		return 0;
	for (i = 0; arts[i] != 0; i++);
	return i;
}

int		is_sorted(register t_art **arts)
{
	register int i;

	if (arts == 0 || *arts == 0 || arts[1] == 0)
		return 1;
	for (i = 0; arts[i + 1] != 0; i++)
		if (strcmp(arts[i]->name, arts[i + 1]->name) > 0)
			return 0;
	return 1;
}

int		main(int argc, char *argv[])
{
	t_art **arts;
	t_dict *dict;
	char *name;
	int size, i;

	if (argc == 2)
		name = argv[1];
	else
		name = "Guernica";
	puts("Using pre-sorted art.txt file");
	arts = parse_file();
	size = length(arts); /* Less optimal size for hash table? */
	/* dict = dictInit(123397); */
	dict = dictInit(size);
	for (i = 0; i < size; i++) {
		if (dictInsert(dict, arts[i]->name, arts[i]) < 0)
			panic("Fatal error: AAAAAAAAAA");
	}
	printf("price of \"%s\" is %d\n", name, searchPrice(dict, name));
	return 0;
}

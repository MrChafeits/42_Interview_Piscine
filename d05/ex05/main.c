#include <stdio.h> //printf, scanf, ...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...
#include <stdlib.h> //malloc, free, exit...
#include <time.h>
#include <math.h>

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
	printUniquePermutations(word);
  stop = clock();
  fprintf(stderr, "clocks(%lu) approx_time(%f)\n", stop-start, (double)(stop-start)/CLOCKS_PER_SEC);

	return (0);
}



// Function used for the test
// Don't go further :)

#define FNV_OFFSET 14695981039346656037ULL
#define FNV_PRIME 1099511628211ULL
size_t	hash(char *input){
  register size_t i;

	for (i = FNV_OFFSET; *input; input++){
    i *= FNV_PRIME;
    i ^= *input;
	}
	return (i);
}

int	dictInsert(struct s_dict *dict, char *key, int value)
{
	int pos;
	struct s_item *tmp;
	struct s_item *tmpBefore;

	if (!dict || !key)
		return (-1);

	pos = hash(key) % dict->capacity;
	tmpBefore = NULL;
	tmp = dict->items[pos];

	//add the new item using push front method
	while (tmp){
		tmpBefore = tmp;
		tmp = tmp->next;
	}
	if (NULL == (tmp = calloc(1, sizeof(struct s_item))))
		return (0);
	if (tmpBefore != NULL)
		tmpBefore->next = tmp;
	else
		dict->items[pos] = tmp;
	tmp->key = strdup(key);
	tmp->value = value;
	tmp->next = NULL;
	return (1);
}

struct s_dict *dictInit(size_t capacity)
{
	struct s_dict *dict;

	if (NULL == (dict = calloc(1, sizeof(struct s_dict))))
		return (NULL);

	dict->capacity = capacity;

	//calculate len
	if (NULL == (dict->items = calloc(sizeof(struct s_item *) , (dict->capacity))))
		return (NULL);

	return (dict);
}

int	dictSearch(struct s_dict *dict, char *key)
{
	int pos;
	struct s_item *tmp;

	pos = hash(key) % dict->capacity;
	tmp = dict->items[pos];
	while (tmp){
		if (strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (-1);
}

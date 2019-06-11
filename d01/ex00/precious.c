#include <stdlib.h>
#include <string.h>
#include "header.h"

t_node *node_create(char c)
{
	t_node *new;

	new = malloc(sizeof(*new));
	if (new == 0)
		return 0;
	new->prev = new->next = new;
	new->c = c;
	return new;
}

t_node *construct_ring(void)
{
	t_node *ring = 0, *tmp = 0, *last = 0;
	const char *str = CS;
	int i = 0, len = 0;

	len = strlen(str);
	for (i = 0; i < len; i++) {
		tmp = node_create(str[i]);
		if (ring == 0) {
			ring = tmp;
		} else {
			last = ring->prev;
			tmp->next = ring;
			tmp->prev = last;
			last->next = tmp;
		}
	}
	return ring;
}

#include <stdio.h>
char *precious(int *text, int size)
{
	t_node *a, *b, *tmp;
	char *res, *sa, *sb;
	int i, len;

	res = malloc((size + 1) * sizeof(*res));
	sa = strdup(CS);
	sb = strdup(CS);
	a = construct_ring();
	b = construct_ring();
	len = strlen(CS);
	for (i = 0; i < len; i++) {
		printf("tmp[%d](%c)\n", i, tmp->c);
		tmp = tmp->next;
	}
	for (i = 0; i < size; i++) {
		res[i] = 'A' + text[i];
	}
	res[i] = 0;
	return res;
}

#include <stdlib.h>
#include <string.h>
#include "header.h"

#include <stdio.h>
t_node *node_create(char c)
{
	t_node *new;

	new = malloc(sizeof(*new));
	if (new == 0)
		return 0;
	new->c = c;
	new->prev = new->next = new;
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
			ring->prev = tmp;
			tmp->prev = last;
			last->next = tmp;
		}
		/* printf("construct tmp[%d](%c)\n", i, tmp->c); */
	}
	return ring;
}

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
	tmp = a;
	for (i = 0; i < len; i++) {
		printf("precious tmp[%d](%c)\n", i, tmp->c);
		tmp = tmp->next;
	}
	for (i = 0; i < size; i++) {
		res[i] = 'A' + text[i];
	}
	res[i] = 0;
	return res;
}

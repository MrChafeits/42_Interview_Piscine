#include <string.h>
#include <stdlib.h>
#include "header.h"

/* Fowler-Noll-Vo family of string hashing functions. */

#define FNV_OFFSET 14695981039346656037ULL
#define FNV_PRIME 1099511628211ULL

size_t	hash(char *input)
{
	register size_t i;

	for (i = FNV_OFFSET; *input; input++) {
		i *= FNV_PRIME;
		i ^= *input;
	}
	return i;
}

#define DEFAULT_HASH_ITEMS 64

t_dict *dictInit(int capacity)
{
	t_dict *new;
	register int i;

	new = malloc(sizeof(t_dict));
	if (capacity == 0)
		capacity = DEFAULT_HASH_ITEMS;
	new->items = malloc(capacity * sizeof(t_item*));
	new->capacity = capacity;
	for (i = 0; i < capacity; i++)
		new->items[i] = 0;
	return new;
}

#define HASH_ITEM(s,t,h) (((h) = hash(s)) & ((t)->capacity - 1))
int dictInsert(t_dict *dict, char *key, t_art *value)
{
	t_item *item;
	long idx;
	size_t hv;

	idx = HASH_ITEM(key, dict, hv);
	item = malloc(sizeof(t_item));
	if (item == 0)
		return -1;
	item->next = dict->items[idx];
	dict->items[idx] = item;
	item->key = key;
	item->value = value;
	return 0;
}

t_art *dictSearch(t_dict *dict, char *key)
{
	t_item *lst;
	long idx;
	size_t hv;

	if (dict == 0 || key == 0)
		return 0;
	idx = HASH_ITEM(key, dict, hv);
	lst = dict->items ? dict->items[idx] : 0;
	while (lst) {
		if (hv == hash(lst->key) && strcmp(lst->key, key) == 0)
			return lst->value;
		lst = lst->next;
	}
	return 0;
}

int searchPrice(t_dict *dict, char *name)
{
	t_art *tmp;

	if (dict == 0 || dict->capacity <= 0 || name == 0)
		return -1;
	tmp = dictSearch(dict, name);
	if (tmp)
		return tmp->price;
	return -1;
}

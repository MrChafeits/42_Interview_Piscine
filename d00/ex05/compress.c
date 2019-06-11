#include <string.h>
#include <stdio.h>
#include "header.h"

typedef struct s_dict t_dict;
typedef struct s_item t_item;

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

int dictInsert(t_dict *dict, char *key, int value)
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

char *stringSmoosh(char *s1, char *s2)
{
	char *res;

	if (s1 == 0 || s2 == 0)
		return 0;
	res = malloc((strlen(s1) + strlen(s2) + 1) * sizeof(*res));
	if (res == 0)
		return 0;
	strcpy(res, s1);
	return strcat(res, s2);
}

char *dictWalkHeader(t_dict *dict)
{
	char *res, *s1, *s2;
	t_item *tmp;
	int rlen, tlen;
	register int i, j;

	res = malloc(2 * sizeof(*res));
	tlen = 0;
	if (res == 0)
		return 0;
	res[0] = '<';
	res[1] = 0;
	rlen = 1;
	for (i = 0; i < dict->capacity; i++) {
		for (j = 0; j < dict->capacity; j++) {
			tmp = dict->items[j];
			while (tmp != 0) {
				if (tmp->value == i) {
					s1 = res;
					s2 = tmp->key;
					if (i && i < dict->capacity) {
						res = stringSmoosh(s1, ",");
						free(s1);
						s1 = res;
					}
					res = stringSmoosh(s1, s2);
					free(s1);
					break;
				}
				tmp = tmp->next;
			}
			if (tmp)
				break;
		}
	}
	s1 = res;
	s2 = ">";
	res = stringSmoosh(s1, s2);
	free(s1);
	return res;
}

int dictSearch(t_dict *dict, char *key)
{
	t_item *lst;
	long idx;
	size_t hv;

	if (dict == 0 || key == 0)
		return -1;
	idx = HASH_ITEM(key, dict, hv);
	lst = dict->items ? dict->items[idx] : 0;
	while (lst) {
		if (hv == hash(lst->key) && strcmp(lst->key, key) == 0)
			return lst->value;
		lst = lst->next;
	}
	return -1;
}
#include <stdio.h>
#define ALPHABETTY "ABCDEFGHIJKLMNOPQRSTUVWXYTabcdefghijklmnopqrstuvwxyt"
char *bookSmoosh(char *header, char *book, t_dict *d)
{
	char *word=0, *tmpword=0, *res=0;
	char pat[3] = {'@', 0, 0};
	int i, idx=0, blen=0, wlen=0;

	wlen = 0;
	blen = strlen(book);
	res = malloc(blen);
	for (i = 0; i < blen;) {
		wlen = strspn(book + i, ALPHABETTY);
		if (!wlen) {
			/* puts("AAAAAAAAAAA"); */
			wlen = strcspn(book + i, ALPHABETTY);
			/* printf("strcspn book[%3d](%02x) wlen(%3d)\n", i, (uint8_t)book[i], wlen); */
			strncpy(res+i, book+i, wlen);
			i += wlen;
			wlen = strspn(book + i, ALPHABETTY);
			/* printf("strspn  book[%3d](%02x) wlen(%3d)\n", i, (uint8_t)book[i], wlen); */
		}
		word = strndup(book+i, wlen);
		if ((idx = dictSearch(d, word)) == -1) {
			/* printf("fdcsrch book[%3d](%02x) wlen(%3d) word(%s)\n", i, (uint8_t)book[i], wlen, word); */
			free(word);
			strncpy(res+i, book+i, wlen);
			i += wlen;
			continue;
		}
		/* printf("strncpy book[%3d](%02x) wlen(%3d) word(%s)\n", i, (uint8_t)book[i], wlen, word); */
		pat[1] = idx + 1;
		strncpy(res+i, pat, 2);
		i += 2;
		free(word);
	}
	tmpword = stringSmoosh(header, res);
	return tmpword;
}

char *compress(char *book, t_dict *dict)
{
	char *header;
	char *res;

	if (book == 0 || *book == 0 || dict == 0)
		return 0;
	header = dictWalkHeader(dict);
	res = bookSmoosh(header, book, dict);
	free(header);
	return res;
}

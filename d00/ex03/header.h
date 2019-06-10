#ifndef _HEADER_H_
#define _HEADER_H_

#include <unistd.h> /* for `size_t' */

typedef struct s_art t_art;
struct s_art {
	char *name;
	int price;
};

typedef struct s_item t_item;
struct s_item {
	char *key; /* Name of the piece */
	t_art *value;
	t_item *next;
};

typedef struct s_dict t_dict;
struct s_dict {
	t_item **items;
	int capacity; /* Currently allocated size of `items' */
};

size_t hash(char *input);
t_dict *dictInit(int capacity);
int dictInsert(t_dict *dict, char *key, t_art *value);
t_art *dictSearch(t_dict *dict, char *key);
int searchPrice(t_dict *dict, char *name);

#endif /* _HEADER_H_ */

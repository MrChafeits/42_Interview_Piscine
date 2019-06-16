#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>
#include <assert.h>

#include "header.h"

#define CHAR_TO_IDX(c) (((int)(c) & 0x1f) - 1)
#if 0
struct s_node {
	char		      c;
	unsigned int	isWord:1;
	struct        s_node	**child;
/* WHY NOT USE A REGULAR ARRAY SINCE THE SIZE IS GUARENTEED TO BE
 * LESS THAN 27?!? WASTE OF SPACE BAD STRUCT GARBO PROGRAM */
};

struct s_trie {
	struct s_node *node;
};
static t_node *nn(int c)
{
	t_node *new = 0;

	new = malloc(sizeof(t_node));
	assert(new != NULL);
	new->c = c;
	new->isWord = 0;
	new->child = 0;
	return new;
}

static void insert(t_node *root, char *key)
{
	register int lvl, idx, i, re, len = strlen(key);
	register t_node *p = root;

	fprintf(stderr, "[DBG: key(%s) len(%d)]\n", key, len);
	for (lvl = 0; lvl < len; ++lvl) {
		re = 0;
		idx = (int)(key[lvl]);
		if (p->child == 0) {
			p->child = malloc(2 * sizeof(t_node*));
			p->child[0] = nn(idx);
			p->child[1] = 0;
		} else {
			for (i = 0; p->child[i]; ++i) {
				if (p->child[i]->c == idx) {
					re = 0;
					p = p->child[i];
					break;
				} else {
					re = 1;
				}
			}
			if (re) {
				p->child = (t_node**)realloc(p->child, ((i + 1) * sizeof(t_node*)));
				assert(p->child != NULL);
				p->child[i] = nn(idx);
				p->child[i+1] = 0;
				p = p->child[i];
			}
		}
	}
	p->isWord = 1;
}
#endif
#if 0
typedef struct s_noodle {
	char c;
	unsigned isWord: 1;
	struct s_noodle *children[256];
} t_noodle;

static t_noodle *noon(int c)
{
	t_noodle *new = 0;

	new = malloc(sizeof(*new));
	assert(new != NULL);
	new->c = c;
	new->isWord = 0;
	for (int i = 0; i < 256; ++i)
		new->children[i] = 0;
	return new;
}

static void inserty(t_noodle *root, char *key)
{
	register int lvl, idx, re, len = strlen(key);
	register t_noodle *p = root;

	for (lvl = 0; lvl < len; ++lvl) {
		re = 0;
		idx = (int)(key[lvl]);
		if (!p->children[idx])
			p->children[idx] = noon(idx);
		p = p->children[idx];
	}
	p->isWord = 1;
}

t_trie *createTrie(char **dictionary)
{
	register int i;
	t_trie *ret;
	t_noodle *node;

	ret = malloc(sizeof(t_trie));
	assert(ret != NULL);
	ret->node = 0;
	node = noon(0);
	for (i = 0; dictionary[i]; ++i)
		inserty(node, dictionary[i]);
	ret->node = (void*)node;
	return ret;
}
#endif
static t_node *nn(int c)
{
	t_node *new = 0;

	new = malloc(sizeof(*new));
	assert(new != NULL);
	new->c = c;
	new->isWord = 0;
	new->child = malloc((257) * sizeof(t_node*));
	assert(new->child != NULL);
	for (int i = 0; i < 257; ++i)
		new->child[i] = 0;
	return new;
}

static void insertWord(t_node *root, char *key)
{
	register int lvl, idx, re, len = strlen(key);
	register t_node *p = root;

	for (lvl = 0; lvl < len; ++lvl) {
		re = 0;
		idx = (int)(key[lvl]);
		if (p && p->child && p->child[idx] == 0)
			p->child[idx] = nn(idx);
		p = p->child[idx];
	}
	p->isWord = 1;
}

t_trie *createTrie(char **dictionary)
{
	register int i;
	t_trie *ret;
	t_node *node;

	ret = malloc(sizeof(t_trie));
	assert(ret != NULL);
	ret->node = 0;
	node = nn(0);
	for (i = 0; dictionary[i]; ++i)
		insertWord(node, dictionary[i]);
	ret->node = node;
	return ret;
}

char *pls(char *word, t_node *node, int wordlen, int curlen)
{
	register int lvl, idx=0, len = wordlen, fuzzy=0;
	register t_node *curdled = node;
	char *ret;

	fprintf(stderr, "[DBG: start word(%s) len(%d) idx(%d)]\n", word, len, idx);
	ret = calloc(len + 1, sizeof(*ret));
	assert(ret != NULL);
	for (lvl = 0; lvl < len; ++lvl) {
		if (word[lvl] != '?') {
			fprintf(stderr, "[DBG: word[lvl] != ? ret(%s) lvl(%d) idx(%d)]\n", ret, lvl, idx);
			idx = (int)(word[lvl]);
		} else {
			idx = 0;
l00ps:
			fuzzy++;
			fprintf(stderr, "[DBG: l00ps ret(%s) lvl(%d) len(%d) idx(%d)]\n", ret, lvl, len, idx);
			for (;idx < 256; ++idx) {
				if (curdled && curdled->child && curdled->child[idx] != 0)
					break;
			}
		}
		if (curdled && curdled->child && curdled->child[idx] == 0 && curdled->isWord == 1 && lvl == len) {
			fprintf(stderr, "[DBG: !child ret(%s) lvl(%d) len(%d) idx(%d)]\n", ret, lvl, len, idx);
			break;
		}
		if (fuzzy) {
			if (lvl < len || curlen < wordlen) {
				idx -= fuzzy;
				fuzzy -= 2;
			} else {
				idx += 1;
			}
			/* for (int i = lvl; i < len; ++i) */
			/* 	ret[i] = word[i]; */
			/* return pls(word, node); */
			goto l00ps;
		}
		if (curdled && curdled->child)
			curdled = curdled->child[idx];
		if (curdled)
			ret[lvl] = curdled->c;
		else
			ret[lvl] = word[lvl];
		curlen++;
		fprintf(stderr, "[DBG: ret(%s) lvl(%d) len(%d) idx(%d)]\n", ret, lvl, len, idx);
	}
	char *tmp;
	if ((tmp = strchr(ret, '?')) != 0) {
		fprintf(stderr, "[DBG: recur ret(%s) lvl(%d) len(%d) idx(%d)]\n", ret, lvl, len, idx);
		for (int i = 0; i + 1 < len; ++i) {
			if (ret[i+1] == '?') {
				ret[i] += 1;
				break;
			}
		}
		fprintf(stderr, "[DBG: recurit ret(%s) lvl(%d) len(%d) idx(%d)]\n", ret, lvl, len, idx);
		return pls(ret, node,strlen(ret), ret - tmp);
	}
	return ret;
}

char *understand(char *word, t_trie *trie)
{
	char *ret;

	assert(word != NULL && trie != NULL && trie->node != NULL);
	ret = pls(word, trie->node, strlen(word), 0);
	/* fprintf(stderr, "[DBG: ret(%s)]\n", ret); */
	return ret;
}

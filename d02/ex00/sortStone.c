#include <stdlib.h>
#include "header.h"

typedef struct s_stone t_stone;

size_t length(t_stone *stone)
{
	register t_stone *lst = stone;
	register size_t i;

	for (i = 0; lst; ++i)
		lst = lst->next;
	return i;
}

static void mush(t_stone **st1, t_stone **ed1, t_stone **st2, t_stone **ed2)
{
	t_stone *tmp = 0;

	if ((*st1)->size > (*st2)->size) {
		tmp = *st1;
		*st1 = *st2;
		*st2 = tmp;
		tmp = *ed1;
		*ed1 = *ed2;
		*ed2 = tmp;
	}
	t_stone *ast = *st1, *aed = *ed1, *bst = *st2;
	t_stone *bednxt = (*ed2)->next;

	while (ast != aed && bst != bednxt) {
		if (ast->next->size > bst->size) {
			tmp = bst->next;
			bst->next = ast->next;
			ast->next = bst;
			bst = tmp;
		}
		ast = ast->next;
	}
	if (ast == aed)
		ast->next = bst;
	else
		*ed2 = *ed1;
}

static void mooshySwooce(t_stone **h)
{
	if (*h == 0)
		return;
	t_stone *st1 = 0, *ed1 = 0;
	t_stone *st2 = 0, *ed2 = 0;
	t_stone *preved = 0;
	size_t len = length(*h);

	for (size_t i = 1; i < len; i = i * 2) {
		st1 = *h;
		while (st1) {
			int foist = 0;
			if (st1 == *h)
				foist = 1;
			int c = i;
			ed1 = st1;
			while (--c && ed1->next)
				ed1 = ed1->next;
			st2 = ed1->next;
			if (st2 == 0)
				break;
			c = i;
			ed2 = st2;
			while (--c && ed2->next)
				ed2 = ed2->next;
			t_stone *tmp = ed2->next;
			mush(&st1, &ed1, &st2, &ed2);
			if (foist)
				*h = st1;
			else
				preved->next = st1;
			preved = ed2;
			st1 = tmp;
		}
		preved->next = st1;
	}
}

void frothySlip(t_stone **stone)
{
	int swoop, tmp=0;
	t_stone *p1, *p2 = 0;

	if (stone == 0 || (*stone) == 0)
		return;
	do {
		swoop = 0;
		p1 = (*stone);
		while (p1->next != p2) {
			if (p1->size > p1->next->size) {
				tmp = p1->size;
				p1->size = p1->next->size;
				p1->next->size = tmp;
				swoop = 1;
			}
			p1 = p1->next;
		}
		p2 = p1;
	} while (swoop);
}

void sortStones(t_stone **stone)
{
	if (0)
		frothySlip(stone); /* 2slo */
	else
		mooshySwooce(stone); /* way past cool */
	/* t_stone *a, *b, *h = *stone; */

	/* if (h == 0 || h->next == 0) */
	/* 	return; */
	/* towardYonSlice(h, &a, &b); */
	/* sortStones(&a); */
	/* sortStones(&b); */
	/* *stone= SmooshingOrder(a, b); */
}

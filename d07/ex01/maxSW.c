#include "header.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_max t_max;
#if 0
struct s_max {
    int *max;
    int length;
};
#endif

typedef struct s_dequeNode t_dequeNode;
#if 0
struct s_dequeNode {
    int value;
    struct s_dequeNode *next, *prev;
};
#endif

typedef struct s_deque t_deque;
#if 0
struct s_deque {
    struct s_dequeNode *first, *last;
};
#endif

t_deque *dequeInit(void)
{
    t_deque *new = calloc(1, sizeof(*new));
    if (new == 0)
        return 0;
    return new;
}

void pushFront(t_deque *deque, int value)
{
    t_dequeNode *new;

    if (deque == 0)
        return;
    new = calloc(1, sizeof(*new));
    if (new == 0)
        return;
    new->value = value;
    if (deque->first != 0)
        deque->first->prev = new;
    else
        deque->last = new;
    new->next = deque->first;
    deque->first = new;
}

void pushBack(t_deque *deque, int value)
{
    t_dequeNode *new;

    if (deque == 0)
        return;
    new = calloc(1, sizeof(*new));
    if (new == 0)
        return;
    new->value = value;
    if (deque->last != 0)
        deque->last->next = new;
    else
        deque->first = new;
    new->prev = deque->last;
    deque->last = new;
}

int popFront(t_deque *deque)
{
    t_dequeNode *tmp;
    int ret;

    if (deque == 0 || deque->first == 0)
        return ~0;
    if (deque->first == deque->last)
        deque->last = 0;
    tmp = deque->first;
    ret = tmp->value;
    deque->first = tmp->next;
    if (deque->first)
        deque->first->prev = 0;
    free(tmp);
    return ret;
}

int popBack(t_deque *deque)
{
    t_dequeNode *tmp;
    int ret;

    if (deque == 0 || deque->last == 0)
        return ~0;
    if (deque->first == deque->last)
        deque->first = 0;
    tmp = deque->last;
    ret = tmp->value;
    deque->last = tmp->prev;
    if (deque->last)
        deque->last->next = 0;
    free(tmp);
    return ret;
}

static int max(int a, int b) { return a > b ? a : b; }

t_max *maxSlidingWindow(int *arr, int n, int k)
{
    t_max *ret;
    t_deque *tmp = dequeInit();
    int i, j, h, t;

    if (!arr || n < 1 || k < 1)
        return 0;
    ret = calloc(1, sizeof(*ret));
    if (!ret)
        return 0;
    ret->max = calloc(n, sizeof(int));
    for (i = 0; i + k <= n; i++) {
        t = 0;
        for (j = i; j < i + k; j++)
            t = max(arr[j], t);
        pushFront(tmp, t);
        t = 0;
    }
    h = 0;
    while (tmp->first != 0 && tmp->last != 0)
        ret->max[h++] = popBack(tmp);
    ret->length = h;
    return ret;
}

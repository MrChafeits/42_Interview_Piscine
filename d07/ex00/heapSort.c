#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct s_art t_art;
/*
struct s_art {
    char *name;
    int price;
};
*/

static void artswap(register t_art **p1, register t_art **p2)
{
    register t_art *tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

int artcmp(const void *p1, const void *p2)
{
    return strcmp((*(t_art**)p1)->name, (*(t_art**)p2)->name);
}

static void newheapify(t_art **arr, int n, int i)
{
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && artcmp(arr+left, arr+largest) > 0)
        largest = left;
    if (right < n && artcmp(arr+right, arr+largest) > 0)
        largest = right;
    if (largest != i) {
        artswap(arr+i, arr+largest);
        newheapify(arr, n, largest);
    }
}

void heapSort(t_art **masterpiece, int n)
{
    int i;

    if (!masterpiece || !*masterpiece || n <= 1)
        return;
    for (i = n / 2 - 1; i >= 0; i--) {
        newheapify(masterpiece, n, i);
    }
    for (i = n - 1; i >= 0; i--) {
        artswap(masterpiece, masterpiece+i);
        newheapify(masterpiece, i, 0);
    }
}

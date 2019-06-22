#include "header.h" /* structs... */
#include <stdlib.h> /* calloc */
#include <string.h> /* strcmp */
#include <limits.h> /* INT_MAX */

static inline int min(int a, int b) { return a < b ? a : b; }

t_sellers *closestSellers(t_graph *parisPlaces, char *youAreHere)
{
    t_sellers *ret;
    t_graph *g;
    t_node *n;
    t_queue *q, *qq;
    int i, j, dist, tmp;

    if (parisPlaces == 0 || youAreHere == 0) /* Sanity check */
        return 0;
    /* Boilerplate initialization */
    g = parisPlaces;
    q = queueInit();
    qq = queueInit();
    if (q == 0 || qq == 0) /* More sanity checking */
        return 0;
    /* Iterate through array of places to find our starting point */
    for (i = 0; g->places[i]; i++) {
        if (strcmp(g->places[i]->name, youAreHere) == 0) {
            /* Found it, so lets enqueue it and break */
            g->places[i]->visited = -1;
            enqueue(q, g->places[i]);
            break;
        }
    }
    /* Setup for the Depth-First Search */
    j = 0;
    tmp = INT_MAX;
    dist = 0;
    while (q->first != 0 || q->last != 0) {
        /* Pop off the front of the queue to begin */
        n = dequeue(q);
        /* Is this node one of the few we are looking for? */
        if (n->hasCerealBar == 1) {
            tmp = min(tmp, n->visited);
            /* Make sure it is within the minimum acceptable distance */
            if (n->visited == tmp) {
                enqueue(qq, n);
                j++;
            }
        }
        /* Iterate through connections */
        for (i = 0; n->connectedPlaces[i] != 0; i++) {
            if (n->connectedPlaces[i]->visited == 0) {
                if (n->visited == -1)
                    dist = 1; /* Initialize distance for first run */
                else
                    dist = n->visited + 1; /* otherwise increment */
                /* Take advantage of marking nodes visited with their distance */
                n->connectedPlaces[i]->visited = dist;
                enqueue(q, n->connectedPlaces[i]);
            }
        }
    }
    ret = calloc(1, sizeof(*ret));
    ret->distance = tmp;
    ret->placeNames = calloc(j + 1, sizeof(char*));
    for (i = 0; i < j; i++) {
        n = dequeue(qq);
        ret->placeNames[i] = n->name;
    }
    ret->placeNames[i] = 0;
    return ret;
}

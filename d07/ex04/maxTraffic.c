#include "header.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>

static int isEmpty(t_queue *q)
{
    return (q == 0 || q->first == 0 || q->last == 0);
}

float maxTraffic(t_graph *parisPlaces, char *eventHere)
{
    t_graph *g;
    t_queue *qsink, *qsource, **pred;
    t_node *t = 0, *edge = 0, *cur = 0;
    float ret = 0., **pot = 0, flubbo;
    int i, j, s, tidx = 0, num_nodes = 0, num_streets = 0, flow = 0;

    qsink = queueInit();
    qsource = queueInit();
    if (parisPlaces == 0 || eventHere == 0 || qsink == 0 || qsource == 0) {/* Sanity check */
        fprintf(stderr, "parisPlaces(%p) eventHere(%p) qsink(%p) qsource(%p)\n",
                parisPlaces, eventHere, qsink, qsource);
error:
        return -1.;
    }
    g = parisPlaces;
    for (i = 0; g->places[i] != 0; i++, num_nodes++) {
        if (t == 0 && strcmp(g->places[i]->name, eventHere) == 0) {
            tidx = i;
            t = g->places[i];
            for (num_streets = 0; t->connectedPlaces[num_streets] != 0; num_streets++);
            t->visited = -1;
        } else {
            enqueue(qsource, g->places[i]);
        }
    }
    pred = calloc(num_nodes, sizeof(*pred));
    if (pred == 0) {
        fprintf(stderr, "pred failed to allocate memory\n");
        goto error;
    }
    pot = calloc(num_nodes, sizeof(float*));
    if (pot == 0) {
        fprintf(stderr, "pot failed to allocate memory\n");
        goto error;
    }
    for (i = 0; i < num_nodes; i++) {
        pot[i] = calloc(num_nodes, sizeof(float));
        pred[i] = queueInit();
        if (pot[i] == 0 || pred[i] == 0) {
            fprintf(stderr, "pot[%1$d](%2$p) pred[%1$d](%3$p)failed to allocate memory\n",
                    i, pot[i], pred[i]);
            goto error;
        }
    }
    s = 0;
    do {
        enqueue(qsink, t);
        while (qsink->first != 0 && qsink->last != 0) {
            if ((cur = dequeue(qsink)) != 0) {
                flow = 0;//cur->population;
                for (i = 0; (edge = cur->connectedPlaces[i]) != 0; i++) {
                    for (j = 0; j < num_nodes; j++) {
                        if (isEmpty(pred[j]) && edge != t) {
                            edge->visited = flow + edge->population;
                            enqueue(pred[j], edge);
                            enqueue(qsink, edge);
                        }
                    }
                }
            }
        }
        for (j = 0; j < num_nodes; j++) {
            if (isEmpty(pred[j]) == 0) {
                flubbo = FLT_MAX;
                for (i = 0; (edge = dequeue(pred[j])) != 0; i++) {
                    flubbo = fmin(flubbo, edge->population);
                }
                for (i = 0; (edge = dequeue(pred[j])) != 0; i++) {
                    edge->visited = edge->population + flubbo;
                    pot[j][i] = edge->population - flubbo;
                }
                ret = ret + flubbo;
                /* printf("j(%d) ret(%.1f) flubbo(%.1f)\n", j, ret, flubbo); */
            }
        }
    } while (isEmpty(pred[tidx]) == 0);
    #if 0
    while (qsource->first != 0 && qsource->last != 0) {
        /* TODO: BFS and get shortest paths, then set the traffic in pot[s]
         * also consider Edmonds-Karp for this problem. */
        n = dequeue(qsource);
    }
    #endif
    return ret - flubbo;
}

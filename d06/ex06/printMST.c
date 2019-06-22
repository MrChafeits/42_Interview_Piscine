#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Print the minimum spanning tree (AGH)*/
typedef struct s_node t_node;
/*
struct s_node {
    int id;               index of the node in the graph
    char *name;           name of the node
    t_edge **edges;       null-terminated array of edges
};
*/
typedef struct s_edge t_edge;
/*
struct s_edge {
    int dist;             distance to the destination node
    t_node *dest;         destination node
};
*/
typedef struct s_graph t_graph;
/*
struct s_graph {
    t_node **nodes;       null-terminated array of all nodes in the graph
};
*/

int min(int a, int b) { return a < b ? a : b; }
/*
Distance : Edges
      20 : Node 0 - Node 1
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa
*/
#define ADJMAT_SIZE 256
void printMST(t_graph *graph)
{
    char seen[ADJMAT_SIZE][ADJMAT_SIZE];
    int i, j, h, s, d;
    t_edge *miniboi=0;

    if (!graph)
        return;
    for (i = 0; i < ADJMAT_SIZE; i++)
        for (j = 0; j < ADJMAT_SIZE; j++)
            seen[i][j] = 0;
    h = (0x7fffffff);
    for (i = 0; graph->nodes[i] != 0; i++) {
        #if 0
        printf("node(%d) id(%d) name(%s) edges {\n",i,
               graph->nodes[i]->id,
               graph->nodes[i]->name);
        #endif
        for (j = 0; graph->nodes[i]->edges[j] != 0; j++) {
            s = graph->nodes[i]->id;
            d = graph->nodes[i]->edges[j]->dest->id;
            if (seen[s][d] || seen[d][s])
                continue;
            h = min(h, graph->nodes[i]->edges[j]->dist);
            if (h == graph->nodes[i]->edges[j]->dist) {
                miniboi = graph->nodes[i]->edges[j];
            }
            seen[s][d] = h;
            seen[d][s] = h;
            #if 0
            printf("\tedge(%d) dist(%d) dest{id(%d) name(%s)}\n",j,
                   graph->nodes[i]->edges[j]->dist,
                   graph->nodes[i]->edges[j]->dest->id,
                   graph->nodes[i]->edges[j]->dest->name);
            #endif
        }
        h = (0x7fffffff);
        printf("%8d : %s - %s\n", miniboi->dist,graph->nodes[i]->name, miniboi->dest->name);
    }
}

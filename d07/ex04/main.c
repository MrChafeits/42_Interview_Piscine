#include <stdio.h> //printf, scanf, ...
#include <string.h> //memcpy, strlen, ...
#include <unistd.h> //fork, write, sleep...
#include <stdlib.h> //malloc, free, exit...
#include <time.h>

#include "header.h"

int main(int argc, char *argv[])
{
	struct s_graph *graph;
  char *filename, *start;
  int fw;
  float res;

  if (argc == 2)
      filename = argv[1];
  else if (argc == 1)
      filename = "squares.txt";
  else {
      fprintf(stderr, "Usage: %s [optional filename]\n", *argv);
      return 1;
  }

	/*-------------------
	launch your test here
	--------------------*/
  graph = getSquares(filename);
  if (argc == 1) {
      res = maxTraffic(graph, "Place du Louvre");
      printf("%20s : %.1f\n%22s(497301.2)\n", "Place du Louvre", res,"");

      res = maxTraffic(graph, "Place Pigalle");
      printf("%20s : %.1f\n%22s(449797.3)\n", "Place Pigalle", res, "");

      res = maxTraffic(graph, "Place des Invalides");
      printf("%20s : %.1f\n%22s(512979.1)\n", "Place des Invalides", res, "");

      res = maxTraffic(graph, "I do not exist");
      printf("%s : %.1f\n%22s(-1.0)\n", "I do not exist", res, "");
  } else {
      start = "Node 3";
      fw = strlen(start);
      res = maxTraffic(graph, start);
      if (strcmp(filename, "example1.txt") == 0)
          printf("%-*s : %.1f\n%*s(30.0)\n", fw, start, res, fw+2, "");
      else if (strcmp(filename, "example2.txt") == 0)
          printf("%-*s : %.1f\n%*s(20.0)\n", fw, start, res, fw+2, "");
      else
          printf("%-*s : %.1f\n", fw, start, res);
  }

  return (0);
}



// Function used for the test
// Don't go further :)

//QUEUE

void enqueue(struct s_queue *queue, void *item) {
	struct s_queueItem* elem;

	if (!(elem = (struct s_queueItem *)calloc(1, sizeof(struct s_queueItem))))
		return;
	elem->item = item;
	elem->next = NULL;
	if (queue->last) {
		queue->last->next = elem;
	}
	queue->last = elem;
	if (queue->first == NULL) {
		queue->first = queue->last;
	}
}

void *dequeue(struct s_queue *queue) {
	struct s_queueItem *elem;
	void *item;

	if (queue->first == NULL)
		return (NULL);
	elem = queue->first;
	item = elem->item;
	queue->first = elem->next;
	if (queue->first == NULL) {
		queue->last = NULL;
	}
	free(elem);
	return (item);
}

struct s_queue *queueInit(void)
{
	struct s_queue *queue;

	queue = calloc(1, sizeof(struct s_queue));
	if (!queue)
		return (NULL);
	queue->first = NULL;
	queue->last = NULL;
	return (queue);
}

//OTHER

struct s_node **getNetwork(FILE *f) {
	long int		id2;
	int				i, size;
	struct s_node	**connectedPlaces;

	fscanf(f, "%d\n", &size);
	if (!(connectedPlaces = calloc(sizeof(struct s_node *) , (size + 1))))
		return (NULL);
	i = 0;
	while (i < size && fscanf(f, "%ld\n", &id2) > 0) {
		connectedPlaces[i] = (struct s_node *)(id2 + 1);
		i++;
	}
	connectedPlaces[i] = NULL;
	return (connectedPlaces);
}

void update(struct s_graph *graph) {
	struct s_node	**places;
	struct s_node	**connectedPlaces;

	places = graph->places;
	for (int i = 0; places[i]; i++) {
		connectedPlaces = places[i]->connectedPlaces;
		for (int j = 0; connectedPlaces[j]; j++) {
			connectedPlaces[j] = places[(int)(connectedPlaces[j]) - 1];
		}
	}
}

struct s_graph *getSquares(char *filename) {
	FILE			*f;
	struct s_graph *graph;
	size_t 			linecap = 0;
	ssize_t 		linelen;
	int				i, size;
	char			*name = NULL;

	if (!(graph = calloc(1, sizeof(struct s_graph))))
		return (NULL);
	if (!(f = fopen(filename, "r"))) {
		printf("Couldn't find %s\n", filename);
		exit(1);
	}
	fscanf(f, "%d\n", &size);
	if (!(graph->places = calloc(sizeof(struct s_node *) , (size + 1))))
		return (NULL);
	i = 0;
	while (i < size && (linelen = getline(&name, &linecap, f)) > 0) {
		name[linelen - 1] = 0;
		if (!(graph->places[i] = calloc(1, (sizeof(struct s_node)))))
			return (NULL);
		graph->places[i]->name = name;
		graph->places[i]->visited = 0;
		fscanf(f, "%d\n", &(graph->places[i]->population));
		if (!(graph->places[i]->connectedPlaces = getNetwork(f)))
			return (NULL);
		name = NULL;
		i++;
	}
	graph->places[i] = NULL;
	update(graph);
	return (graph);
}

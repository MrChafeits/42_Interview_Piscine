#include "header.h"
#include <stdlib.h>

typedef struct s_node t_node;
typedef struct s_queue t_queue;

t_queue *queueInit(void) {
  t_queue *new;

  new = malloc(sizeof(*new));
  if (new != 0)
    new->first = new->last = 0;
  return new;
}

char *dequeue(t_queue *queue) {
  t_node *tmp;
  char *ret;

  if (isEmpty(queue))
    return 0;
  tmp = queue->first;
  queue->first = queue->first->next;
  ret = tmp->message;
  free(tmp);
  return ret;
}

void enqueue(t_queue *queue, char *message) {
  t_node *new;

  if (queue == 0)
    return;
  new = malloc(sizeof(*new));
  new->message = message;
  new->next = 0;
  if (queue->first == 0)
    queue->first = new;
  else
    queue->last->next = new;
  queue->last = new;
}

char *peek(t_queue *queue) {
  char *ret;

  ret = 0;
  if (queue != 0 && queue->first != 0)
    ret = queue->first->message;
  return ret;
}

int isEmpty(t_queue *queue) { return !(queue != 0 && queue->first != 0); }

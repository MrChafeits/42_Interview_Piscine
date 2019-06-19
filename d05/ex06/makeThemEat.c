#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_people t_people;

int isPossible(t_people **people, int nbTable, int totalTime)
{
  long tmp, i;

  i = tmp = 0;
  while (people[i] != 0) {
    tmp += people[i]->time;
    i++;
  }
  return tmp / nbTable <= totalTime;
}

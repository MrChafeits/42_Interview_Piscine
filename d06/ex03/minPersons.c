#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* 50 numbers on the wheel, betting on the right one wins.
 How many people need to be in the room for two to bet on the same number */

int minPersons(int elements, int minPercentage)
{
  double pcnt=0;
  int ct;

  for (ct = 2; pcnt * 100 < minPercentage; ct++) {
    pcnt = 1.0 - pow((double)(elements-1)/elements, (ct *(ct-1))/2);
  }
  return ct-1;
}

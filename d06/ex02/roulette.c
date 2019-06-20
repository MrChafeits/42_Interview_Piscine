#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Wheel: 37 pockets, 18 red, 18 black, 1 green
   Bossman wants to win $500 in less than 3 games from $100 by only betting red
   and if the goal is exceeded, then the remaining rounds are not played */

double probabilityWin(double initDollars, double wantedDollars, int nbGame)
{
  if (nbGame < 0 || initDollars == 0)
    return 0;
  if (initDollars >= wantedDollars)
    return 1;
  return ((18 * probabilityWin(initDollars * 2, wantedDollars, nbGame - 1) +
           probabilityWin(initDollars / 2, wantedDollars, nbGame - 1)) / 37);
}

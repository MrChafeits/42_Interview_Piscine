#include "header.h"

static int Add(int x, int y)
{
  if (y ^ 0)
    return Add(x ^ y, (x & y) << 1);
  else
    return x;
}

static int Sub(int x, int y)
{
  if (y ^ 0)
    return Sub(x ^ y, (~x & y) << 1);
  else
    return x;
}

static int recur(unsigned p, int ret)
{
  if (p ^ 0)
    return recur(p & Sub(p, 1), Add(ret, 1));
  else
    return ret;
}

int occupiedPlaces(unsigned int parkingRow)
{
  return recur(parkingRow, 0);
}
/*
int occupiedPlaces(unsigned int parkingRow)
{
  int ret;

  for (ret = 0; parkingRow; ret++)
    parkingRow &= (parkingRow - 1);
  return ret;
}
*/

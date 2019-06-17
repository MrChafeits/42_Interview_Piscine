#include "header.h"

static int Not(unsigned v)
{
  return ((((((((((((v >> 16) | v) >> 8) | ((v >> 16) | v)) >> 4)
               | ((((v >> 16) | v) >> 8) | ((v >> 16) | v))) >> 2)
             | ((((((v >> 16) | v) >> 8) | ((v >> 16) | v)) >> 4)
               | ((((v >> 16) | v) >> 8) | ((v >> 16) | v)))) >> 1)
           | ((((((((v >> 16) | v) >> 8) | ((v >> 16) | v)) >> 4)
               | ((((v >> 16) | v) >> 8) | ((v >> 16) | v))) >> 2)
             | ((((((v >> 16) | v) >> 8) | ((v >> 16) | v)) >> 4)
               | ((((v >> 16) | v) >> 8) | ((v >> 16) | v))))) ^ 1) & 1);
}

static int Add(int x, int y)
{
  if (y)
    return Add(x ^ y, (x & y) << 1);
  else
    return x;
}

static int Sub(int x, int y)
{
  if (y)
    return Sub(x ^ y, (~x & y) << 1);
  else
    return x;
}

int carPosRecur(unsigned p, int i, int ret)
{
  if (Not(i & p))
    return carPosRecur(p, i << 1, Add(ret, 1));
  else
    return ret;
}

static int isPowerOfTwo(unsigned n)
{
  if (n)
    return Not(n & Sub(n, 1));
  else
    return 0;
}

int carPosition(unsigned int parkingRow)
{
  if (isPowerOfTwo(parkingRow))
    return carPosRecur(parkingRow, 1, 0);
  else
    return ~0;
}

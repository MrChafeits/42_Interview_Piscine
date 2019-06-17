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

#if 0
static int Add(int x, int y)
{
  if (y)
    return Add(x ^ y, (x & y) << 1);
  else
    return x;
}
#endif

static int Sub(int x, int y)
{
  if (y)
    return Sub(x ^ y, (~x & y) << 1);
  else
    return x;
}

static int carPosRecur(unsigned p, int i, int ret)
{
  if (Not(i & p))
    return carPosRecur(p, i >> 1, Sub(ret, 1));
  else
    return ret;
}

int leftmostCar(unsigned parkingRow)
{
  if (parkingRow)
    return carPosRecur(parkingRow, 2147483648U, 31);
  else
    return ~0;
}

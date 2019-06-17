#include "header.h"

#if 0
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
#endif

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

static unsigned unsetBitsRange(unsigned n, unsigned l, unsigned r)
{
  return (n ^ (Sub(1 << r, 1) ^ Sub((1 << Sub(l, 1)), 1)));
}

unsigned clearBits(unsigned parkingRow, int n)
{
  return (parkingRow & unsetBitsRange(~0, Add(n, 1), 0));
}

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

static int Sub(int x, int y)
{
  if (y)
    return Sub(x ^ y, (~x & y) << 1);
  else
    return x;
}
#endif

static int Add(int x, int y)
{
  if (y)
    return Add(x ^ y, (x & y) << 1);
  else
    return x;
}

static int maxSeqBits(unsigned p, unsigned ret)
{
  if (p)
    return maxSeqBits(p & (p << 1), Add(ret, 1));
  else
    return ret;
}

int longestSequence(unsigned parkingRow)
{
  return maxSeqBits(parkingRow, 0);
}

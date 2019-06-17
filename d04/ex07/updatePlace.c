#include "header.h"

unsigned int updatePlace(unsigned int parkingRow, int pos, int value)
{
  return value ? (parkingRow | (1 << pos)) : (parkingRow & ~(1 << pos));
}

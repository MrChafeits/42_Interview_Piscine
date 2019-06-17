#include "stdio.h"
#include "header.h"

int Add(int x, int y)
{
  if (y ^ 0)
    return Add(x ^ y, (x & y) << 1);
  else
    return x;
}

int not(unsigned v)
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
#if 1
int isFilled(unsigned int parkingRow)
{
  return not(parkingRow & Add(parkingRow, 1));
}
#else
int isFilled(unsigned int parkingRow)
{
  if (0b1111111111111111111111111111111 ^ parkingRow)
    goto thirty;
  goto end;
 thirty:
  if (0b111111111111111111111111111111 ^ parkingRow)
    goto twentynine;
  goto end;
 twentynine:
  if (0b11111111111111111111111111111 ^ parkingRow)
    goto twentyeight;
  goto end;
 twentyeight:
  if (0b1111111111111111111111111111 ^ parkingRow)
    goto twentyseven;
  goto end;
 twentyseven:
  if (0b111111111111111111111111111 ^ parkingRow)
    goto twentysix;
  goto end;
 twentysix:
  if (0b11111111111111111111111111 ^ parkingRow)
    goto twentyfive;
  goto end;
 twentyfive:
  if (0b1111111111111111111111111 ^ parkingRow)
    goto twentyfour;
  goto end;
 twentyfour:
  if (0b111111111111111111111111 ^ parkingRow)
    goto twentythree;
  goto end;
 twentythree:
  if (0b11111111111111111111111 ^ parkingRow)
    goto twentytwo;
  goto end;
 twentytwo:
  if (0b1111111111111111111111 ^ parkingRow)
    goto twentyone;
  goto end;
 twentyone:
  if (0b111111111111111111111 ^ parkingRow)
    goto twenty;
  goto end;
 twenty:
  if (0b11111111111111111111 ^ parkingRow)
    goto nineteen;
  goto end;
 nineteen:
  if (0b1111111111111111111 ^ parkingRow)
    goto eighteen;
  goto end;
 eighteen:
  if (0b111111111111111111 ^ parkingRow)
    goto seventeen;
  goto end;
 seventeen:
  if (0b11111111111111111 ^ parkingRow)
    goto sixteen;
  goto end;
 sixteen:
  if (0b1111111111111111 ^ parkingRow)
    goto fifteen;
  goto end;
 fifteen:
  if (0b111111111111111 ^ parkingRow)
    goto fourteen;
  goto end;
 fourteen:
  if (0b11111111111111 ^ parkingRow)
    goto thirteen;
  goto end;
 thirteen:
  if (0b1111111111111 ^ parkingRow)
    goto twelve;
  goto end;
 twelve:
  if (0b111111111111 ^ parkingRow)
    goto eleven;
  goto end;
 eleven:
  if (0b11111111111 ^ parkingRow)
    goto ten;
  goto end;
 ten:
  if (0b1111111111 ^ parkingRow)
    goto nine;
  goto end;
 nine:
  if (0b111111111 ^ parkingRow)
    goto eight;
  goto end;
 eight:
  if (0b11111111 ^ parkingRow)
    goto seven;
  goto end;
 seven:
  if (0b1111111 ^ parkingRow)
    goto six;
  goto end;
 six:
  if (0b111111 ^ parkingRow)
    goto five;
  goto end;
 five:
  if (0b11111 ^ parkingRow)
    goto four;
  goto end;
 four:
  if (0b1111 ^ parkingRow)
    goto three;
  goto end;
 three:
  if (0b111 ^ parkingRow)
    goto two;
  goto end;
 two:
  if (0b11 ^ parkingRow)
    goto one;
  goto end;
 one:
  if (0b1 ^ parkingRow)
    return 0;
 end:
  return 1;
}
#endif

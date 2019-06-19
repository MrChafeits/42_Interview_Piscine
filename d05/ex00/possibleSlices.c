#include <stdio.h>
#include "header.h"

typedef struct s_array t_array;

int arrayResize(t_array *arr);
#if 0
struct s_array {
	int *content;
	int length;
	int sum;
	int capacity;
};

struct s_array *arrayInit(void);
int     arrayAppend(struct s_array *arr, int number);
struct s_array *arrayClone(struct s_array *arr);
void    arrayPrint(struct s_array *arr);
#endif

void findPermsRecur(int *arr, int idx, int num, int rnum)
{
  if (rnum < 0)
    return;
  if (rnum == 0) {
    int i = -1;
    while (++i <= idx)
      i != idx ? printf((i==0?"[%d":", %d"), arr[i]) : printf("]\n");
    if (idx != num && idx != 1 && (i = idx))
      while (--i >= -1)
        i >= 0 ? printf((i==idx-1?"[%d":", %d"), arr[i]) : printf("]\n");
    return;
  }
  int prev = (idx == 0 ? 1 : arr[idx - 1]) - 1;
  while (++prev < num + 1) {
    arr[idx] = prev;
    findPermsRecur(arr, idx + 1, num, rnum - prev);}
}

void printPossibleSlices(int pizzaSize)
{
  int arr[pizzaSize];
  int i = -1;
  while (++i < pizzaSize)
    arr[i] = 0;
  findPermsRecur(arr, 0, pizzaSize, pizzaSize);
}

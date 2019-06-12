#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdio.h>

/*--------------------------------
  !! required structure
  --------------------------------*/
struct s_node {
  int value;
  struct s_node *random;
  struct s_node *next;
};

/*--------------------------------
  :) function you must implement
  --------------------------------*/
struct s_node *cloneGameBoard(struct s_node *node);

/*--------------------------------
  ?? test function used in main
  --------------------------------*/
struct s_node *genRandomSnakesAndLadders(int n);
void printSnakeAndLadders(struct s_node *node, FILE *fp);

/*--------------------------------
  &  your own other function
  --------------------------------*/

#endif /* _HEADER_H_ */

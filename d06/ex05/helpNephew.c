#include "header.h"

/* Nephew is on the nth floor, Big funny Monkey is going to punch m times.
 Calculate Lil' Shits chances of survival. */

double calc(int nStairs, int nPunch, int nephewStair)
{
    double ret, k;

    ret = 0.0;
    k = 1.0 / (double)nStairs;
    if (nStairs <= nephewStair || nPunch <= 0)
        return (nStairs <= nephewStair ? 1 : 0);
    while (nStairs > 0) {
        ret += k * calc(nStairs - 1, nPunch - 1, nephewStair);
        nStairs--;
    }
    return ret;
}

double probaNephewWillLive(int nStairs, int nPunch, int nephewStair)
{
    if (nStairs <= 0 || nPunch < 0 || nephewStair < 0 || nephewStair > nStairs)
        return 0.0;
    return 1.0 - calc(nStairs, nPunch, nephewStair);
}

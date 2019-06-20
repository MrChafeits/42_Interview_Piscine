#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_hotspot t_hotspot;

int selectHotspots(struct s_hotspot **hotspots)
{
    int res, covered;
    register int i;

    if (!hotspots)
        return 0;
    res = covered = 0;
    for (i = 0; hotspots[i]; i++) {
        if (abs(hotspots[i]->pos - hotspots[i]->radius) >= covered) {
            covered = hotspots[i]->pos + hotspots[i]->radius;
            res++;
        }
        if (covered > hotspots[i]->pos + hotspots[i]->radius)
            covered = hotspots[i]->pos + hotspots[i]->radius;
    }
    return (res);
}

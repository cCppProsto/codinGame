#ifndef _MAIN_
#define _MAIN_

#include <stdio.h>

int main()
{
    int lightX;         // the X position of the light of power
    int lightY;         // the Y position of the light of power
    int initialTX;      // Thor's starting X position
    int initialTY;      // Thor's starting Y position
    scanf("%d%d%d%d", &lightX, &lightY, &initialTX, &initialTY);

    int dx = 0;
    int dy = 0;
    while (1)
    {
        int remainingTurns;
        scanf("%d", &remainingTurns);

        dx = (initialTX - lightX) == 0 ? 0 : initialTX - lightX > 0 ? -1 : 1 ;
        dy = (initialTY - lightY) == 0 ? 0 : initialTY - lightY > 0 ? -1 : 1;

        (dy == 0) ? 0 : dy > 0 ? printf("S") : printf("N");
        (dx == 0) ? 0 : dx > 0 ? printf("E") : printf("W");
        printf("\n");

        initialTX += dx;
        initialTY += dy;
    }
    return 0;
}

#endif // _MAIN_

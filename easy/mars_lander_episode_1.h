#ifndef _MAIN_
#define _MAIN_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
* Auto-generated code below aims at helping you parse
* the standard input according to the problem statement.
**/
int main()
{
    int surfaceN; // the number of points used to draw the surface of Mars.
    scanf("%d", &surfaceN);

    for (int i = 0; i < surfaceN; i++)
    {
        int landX; // X coordinate of a surface point. (0 to 6999)
        int landY; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        scanf("%d%d", &landX, &landY);
    }

    int   isDamping     = 0;
    float speed         = 0.0f;
    float acceleration  = 3.711f;
    // game loop
    while (1)
    {
        int X;
        int Y;
        int hSpeed; // the horizontal speed (in m/s), can be negative.
        int vSpeed; // the vertical speed (in m/s), can be negative.
        int fuel; // the quantity of remaining fuel in liters.
        int rotate; // the rotation angle in degrees (-90 to 90).
        int power; // the thrust power (0 to 4).
        scanf("%d%d%d%d%d%d%d", &X, &Y, &hSpeed, &vSpeed, &fuel, &rotate, &power);

        // Write an action using printf(). DON'T FORGET THE TRAILING \n
        // To debug: fprintf(stderr, "Debug messages...\n");

        if (-(vSpeed) >= 45)
            isDamping = 1;

        // 2 integers: rotate power. rotate is the desired rotation angle (should be 0 for level 1), power is the desired thrust power (0 to 4).
        if (isDamping)
        {
            printf("0 4\n");
            if(power < 4)
                acceleration -= power;
            else
                acceleration = 3.711f - 4.f;
        }
        else
            printf("0 0\n");

        speed += acceleration;
        //fprintf(stderr, "calculated speed = %f(%d)\n", speed, (int)speed);
    }

    return 0;
}

#endif // _MAIN_

#ifndef _MAIN_
#define _MAIN_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    freopen("d:\\tmp\\codingame\\data.txt", "r", stdin);

    int width;                              // the number of cells on the X axis
    int height;                             // the number of cells on the Y axis
    char grid[32][32];

    scanf("%d", &width);
    scanf("%d", &height);
    fgetc(stdin);

    //fprintf(stderr, "%i %i\n", width, height);
    for (int i = 0; i < height; i++)
        fgets(grid[i], 32, stdin);          // width characters, each either 0 or .

    for (int i = 1; i < height; i++)
    {
        for(int j = 0; j < width; ++j)
        {
            if(grid[i-1][j] == '0')
            {
                printf("%i %i", j, i-1);
                int isFind = -1;
                int right  = j + 1;
                int down   = i;
                for(; right < width; ++right)
                {
                    if(grid[i-1][right] == '0')
                    {
                        isFind = 1;
                        break;
                    }
                }
                if(isFind == 1)
                    printf(" %i %i", right, i-1);
                else
                    printf(" -1 -1");
                isFind = -1;

                for(; down < height; ++down)
                {
                    if(grid[down][j] == '0')
                    {
                        isFind = 1;
                        break;
                    }
                }
                if(isFind == 1)
                    printf(" %i %i", j, down);
                else
                    printf(" -1 -1");

                printf("\n");
            }
        }
    }

    for(int j = 0; j < width; ++j)
    {
        if(grid[height-1][j] == '0')
        {
            printf("%i %i", j, height-1);
            int isFind = -1;
            int right  = j + 1;
            for(; right < width; ++right)
            {
                if(grid[height-1][right] == '0')
                {
                    isFind = 1;
                    break;
                }
            }
            if(isFind == 1)
                printf(" %i %i", right, height-1);
            else
                printf(" -1 -1");
            isFind = -1;

            printf(" -1 -1");
            printf("\n");
        }
    }
    return 0;
}

#endif // _MAIN_

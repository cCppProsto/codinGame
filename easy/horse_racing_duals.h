#ifndef _MAIN_
#define _MAIN_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 10000001

int main()
{
    freopen("d:\\data.txt", "r", stdin);

    int horseCount          = 0;
    int i                   = 0;
    int j                   = 0;
    int *parray_sort        = 0;
    int min                 = ARRAY_SIZE;
    int j_a                 = -1;
    int j_b                 = -1;
    int tmp                 = 0;

    scanf("%i", &horseCount);
    parray_sort  = (int*)calloc(ARRAY_SIZE, sizeof(int));
    i = 0;
    while(i < horseCount)
    {
        scanf("%i", &j);
        parray_sort[j]++;
        ++i;
    }

    i = 0;
    j = 0;
    while(j < ARRAY_SIZE)
    {
        if(parray_sort[j] > 0)
        {
            if(j_a < 0)
            {
                j_a = j;
                ++i;
            }
            else
                if (j_b < 0)
                {
                    j_b = j;
                    tmp = abs(j_a - j_b);
                    if(tmp < min)
                        min = tmp;

                    j_a = j_b;
                    j_b = -1;
                    ++i;

                    if(i >= horseCount)
                        break;
                }

            parray_sort[j]--;
            if(parray_sort[j] > 0)
                --j;
        }
        ++j;
    }
    free(parray_sort);

    printf("%i\n", min);

    return 0;
}

#endif // _MAIN_

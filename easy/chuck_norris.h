#ifndef _MAIN_
#define _MAIN_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char MESSAGE[101] = { 0 };
    fgets(MESSAGE, 101, stdin);
    char *pm = MESSAGE;
    // 0  1
    // 00 0
    char prev = 0;
    char shift = 6;
    char isNewBlock = 1;

    prev = ((*pm >> shift) & 0x01) ? 1 : 0;
    do
    {
        if (isNewBlock)
        {
            printf("%s", (*pm >> shift) & 0x01 ? "0 " : "00 ");
            isNewBlock = 0;
        }

        while ((shift >= 0) && (prev ? ((*pm >> shift) & 0x01) : !((*pm >> shift) & 0x01)) && (shift-- >= 0))
            printf("0");

        if (shift < 0)
        {
            if ((shift = 6) && (*++pm == '\n') )
                break;
        }
        else
        {
            prev = prev ? 0 : 1;
            isNewBlock = 1;
            printf(" ");
        }

    } while (1);
    return 0;
}


#endif // _MAIN_


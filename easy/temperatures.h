#ifndef _MAIN_
#define _MAIN_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int n, tmp, min = 6000, isNegative = 0;

    scanf("%d", &n); fgetc(stdin);

    if (n == 0 && printf("0\n"))
        return 0;

    while (n-- > 0)
    {
        scanf("%d", &tmp);
        isNegative = abs(tmp) == min ?  isNegative ? 1 : 0 : tmp < 0 ? 1 : 0;
        min        = abs(tmp) < min ? abs(tmp) : min;
    }
    printf("%d\n", isNegative ? -min : min);
    return 0;
}

#endif // _MAIN_

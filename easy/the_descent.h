#ifndef _MAIN_
#define _MAIN_

#include <stdio.h>
#include <stdlib.h>
int main()
{
    int max_i  = 0;
    int m_h[8] = {0};
    while (1)
    {
        max_i = 0;
        for (int i = 0; i < 8; max_i = m_h[i] >= m_h[max_i] ? i : max_i, ++i)
            scanf("%d", &m_h[i]);
        printf("%i\n", max_i);
    }
    return 0;
}

#endif // _MAIN_

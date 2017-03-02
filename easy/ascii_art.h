#ifndef _MAIN_
#define _MAIN_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int L;
    scanf("%d", &L);
    int H;
    scanf("%d", &H);
    fgetc(stdin);

    char T[257];
    fgets(T, 257, stdin);

    int out_l = strlen(T) - 1;

    int char_index = 0;
    // A...Z (65...90)
    // a...z (97...122)

    for (int i = 0; i < H; i++)
    {
        char ROW[1025];
        fgets(ROW, 1025, stdin);

        for (int j = 0; j < out_l; j++)
        {
            char_index = (T[j] >= 65) && (T[j] <= 90) ? T[j] - 65 : (T[j] >= 97) && (T[j] <= 122) ? T[j] - 97 : 26;

            int start = char_index * L;
            int end = start + L;
            for (; start < end; start++)
                printf("%c", ROW[start]);
        }
        printf("\n");
    }

    return 0;
}

#endif // _MAIN_

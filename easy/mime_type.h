#ifndef _MAIN_
#define _MAIN_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char extArray[10000][101] = { 0 };
char mtArray[10000][501] = { 0 };

int main()
{
  freopen("d:\\data4.txt", "r", stdin);

  int N; // Number of elements which make up the association table.
  scanf("%d", &N);

  int Q; // Number Q of file names to be analyzed.
  scanf("%d", &Q);

  int i_e = 0;
  int i_m = 0;
  int j   = 0;

  int hash_i      = 0;
  int *hash_array = (int*)malloc(Q * sizeof(int));

  for (int i = 0; i < N; i++)
  {
    scanf("%s%s", &extArray[i_e++][0], &mtArray[i_m++][0]);

    for (int j = 0; extArray[i_e - 1][j]; ++j)
      extArray[i_e - 1][j] = tolower(extArray[i_e - 1][j]);

    fgetc(stdin);
  }

  for (int i = 0; i < Q; i++)
  {
    char EXTS[11] = { 0 };
    int isRun = 1;
    int isExt = 0;
    int ext_i = 0;
    char ch = 0;

    while (isRun)
    {
      ch = fgetc(stdin);

      switch (ch)
      {
        case EOF:
        case '\n':
        {
          isRun = 0;
          break;
        }
        case '.':
        {
          memset(EXTS, 0, 11);
          ext_i = 0;
          isExt = 1;
          break;
        }
        default:
        {
          if(isExt)
            EXTS[ext_i++] = tolower(ch);
          break;
        }
      }
    }

    int hash_index = -1;
    if(EXTS[0] != 0)
      for (int j = 0; j < N; ++j)
      {
        if (strcmp(&EXTS[0], &extArray[j][0]) == 0)
        {
          hash_index = j;
          break;
        }
      }
    hash_array[hash_i++] = hash_index;
  }

  for (int i = 0; i < Q; i++)
  {
    if (hash_array[i] == -1)
      printf("UNKNOWN\n");
    else
      printf("%s\n", mtArray[hash_array[i]]);
  }
  return 0;
}

#endif // _MAIN_

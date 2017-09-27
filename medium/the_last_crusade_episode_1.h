#ifndef _MAIN_
#define _MAIN_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main()
{
  int W; // number of columns.
  int H; // number of rows.

  int rooms[201][201] = {0};

  freopen("/home/ioleshko/tmp/the_last_crusade_episode_1_1", "r", stdin);

  scanf("%d%d", &W, &H); fgetc(stdin);
  fprintf(stderr, "%i : %i\n", W, H);
  for (int i = 0; i < H; i++)
  {
    int index = 0;
    while(index < W)
    {
      scanf("%i", &(rooms[i][index]));
      index++;
    }
  }

  // the coordinate along the X axis of the exit (not useful for this first mission, but must be read).
  int EX;
  scanf("%d", &EX);
  fprintf(stderr, "%i\n", EX);

  // game loop
  while (1)
  {
    int  XI;
    int  YI;
    char POS[6];
    scanf("%d%d%s", &XI, &YI, POS);

    char roomType = rooms[YI][XI];
    switch(roomType)
    {
      case 1: // only bottom
      case 3:
      case 7:
      case 8:
      case 9:
      case 12:
      case 13:
      {
        YI++;
        break;
      }
      case 2: // left or rigth
      {
        if(POS[0] == 'L')
          XI++;
        else
          XI--;
        break;
      }
      case 4:// left or bottom
      {
        if(POS[0] == 'T')
          XI--;
        else
          YI++;
        break;
      }
      case 5:// right or bottom
      {
        if(POS[0] == 'T')
          XI++;
        else
          YI++;
        break;
      }
      case 6:// right or bottom
      {
        if(POS[0] == 'L')
          XI++;
        else if(POS[0] == 'R')
          XI--;
        break;
      }
      case 10:// only left
      {
        XI--;
        break;
      }
      case 11:// only right
      {
        XI++;
        break;
      }
    }

    // Write an action using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");


    // One line containing the X Y coordinates of the room in which you believe Indy will be on the next turn.
    printf("%i %i\n", XI, YI);
  }

  return 0;
}


#endif // _MAIN_

#ifndef _MAIN_
#define _MAIN_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
  int nbFloors;               // number of floors
  int width;                  // width of the area
  int nbRounds;               // maximum number of rounds
  int exitFloor;              // floor on which the exit is found
  int exitPos;                // position of the exit on its floor
  int nbTotalClones;          // number of generated clones
  int nbAdditionalElevators;  // ignore (always zero)
  int nbElevators;            // number of elevators
}initData;

typedef struct
{
  int cloneFloor;             // floor of the leading clone
  int clonePos;               // position of the leading clone on its floor
  char direction[11];         // direction of the leading clone: LEFT or RIGHT
}gameTickData;

void read_init_data(initData*);
void get_tick_data(gameTickData*);

int main()
{
  //freopen("/home/ioleshko/tmp/donot_panic_1.txt", "r", stdin);
  int floors[100] = {-1};
  initData data;

  read_init_data(&data);

  /*
  fprintf(stderr,"%d %d %d %d %d %d %d %d\n",
          data.nbFloors,  data.width,   data.nbRounds,
          data.exitFloor, data.exitPos, data.nbTotalClones,
          data.nbAdditionalElevators,   data.nbElevators);
  */

  floors[data.nbFloors - 1] = data.exitPos;

  for (int i = 0; i < data.nbElevators; i++)
  {
    int elevatorFloor = 0;
    int floorExit = 0;
    scanf("%d%d", &elevatorFloor, &floorExit);
    floors[elevatorFloor] = floorExit;

    //fprintf(stderr, "%d %d\n", elevatorFloor, floorExit);
  }

  // game loop
  int tickNumber = 0;
  while (tickNumber <= data.nbRounds)
  {
    gameTickData tickData;
    get_tick_data(&tickData);

    switch(tickData.direction[0])
    {
      case 'R':
      {
        if(tickData.clonePos > floors[tickData.cloneFloor])
          printf("BLOCK\n");
        else
          printf("WAIT\n");
        break;
      }
      case 'L':
      {
        if(tickData.clonePos >= floors[tickData.cloneFloor])
          printf("WAIT\n");
        else
          printf("BLOCK\n");
        break;
      }
      case 'N':
      {
        printf("WAIT\n");
        break;
      }
    }

    //fprintf(stderr, "%d %d %s\n", tickData.cloneFloor, tickData.clonePos, tickData.direction);
    ++tickNumber;
  }
  return 0;
}

//------------------------------------------------------------------------------
void read_init_data(initData *apData)
{
  scanf("%d%d%d%d%d%d%d%d",
        &apData->nbFloors,
        &apData->width,
        &apData->nbRounds,
        &apData->exitFloor,
        &apData->exitPos,
        &apData->nbTotalClones,
        &apData->nbAdditionalElevators,
        &apData->nbElevators);
}
//------------------------------------------------------------------------------
void get_tick_data(gameTickData *apData)
{
  scanf("%d%d%s", &apData->cloneFloor, &apData->clonePos, &apData->direction[0]);

  //fprintf(stderr, "%d %d %s\n", apData->cloneFloor, apData->clonePos, apData->direction);
}

#endif // _MAIN_

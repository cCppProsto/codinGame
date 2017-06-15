#ifndef _MAIN_
#define _MAIN_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum
{
  SOUTH
  , EAST
  , NORTH
  , WEST
}eDirection;

typedef enum
{
  CHECK_MOVING
  , MOVE
  , DIRECTION_CALC
  , END
  , LOOP
}eState;

typedef enum
{
  EMPTY      // ' '
  , WALL       // '#'
  , OBSTACLE   // 'X'
  , FINISH     // '$'
  , S          // 'S'
  , E          // 'E'
  , N          // 'N'
  , W          // 'W'
  , BEER       // 'B'
  , INVERT     // 'I'
  , TELEPORT   // 'T'
}eMap;


typedef struct
{
  int line;
  int ceil;
}sPos;

typedef struct
{
  int        isBeer;
  int        isInvert;
  eDirection direction;
  sPos       pos;
}sBenderData;

typedef struct
{
  int   width;
  int   height;
  eMap  *map;
  sPos  teleportPos1;
  sPos  teleportPos2;
}sMapData;

typedef struct
{
  eDirection dir;
  sPos       pos;
}sHistory;


sHistory history[100 * 100] = { { -1, -1 }, SOUTH };
int index = 0;
int check_count = 3;

//-----------------------------------------------------------------------------
void init_data(sBenderData*, sMapData *);

eMap get_map(int, int, sMapData *);
void set_map(int, int, sMapData *, eMap);

void print_map(sMapData *);
void load_map(sMapData *, sBenderData *);

int is_move(sMapData*, sBenderData*);
void move(sMapData*, sBenderData*);
void calc_direction(sMapData*, sBenderData*);

void add_history_and_check_loop(sBenderData *apBender, int *);
int is_equal(sHistory *, sHistory *);
//-----------------------------------------------------------------------------

int main()
{
  freopen("d:\\tmp\\codingame\\data.txt", "r", stdin);

  sBenderData bender;
  sMapData    map;

  init_data(&bender, &map);

  scanf("%d%d", &map.height, &map.width); fgetc(stdin);

  /*
  printf("%d %d\n", map.height, map.width);
  for (int i = 0; i < map.height; i++)
  {
    char row[102];
    fgets(row, 102, stdin);
    printf("%s", row);
  }
  */
  //print_map(&map);

  load_map(&map, &bender);

  eState state = CHECK_MOVING;
  eDirection dirPrev = SOUTH;
  eDirection dirCur = SOUTH;

  int debug = 0;
  while (1)
  {
    switch (state)
    {
      case CHECK_MOVING:
      {
        if (is_move(&map, &bender))
          state = MOVE;
        else
          state = DIRECTION_CALC;
        break;
      }
      case MOVE:
      {
        int isLoop = 0;

        if (debug == 114)
          debug = 114;

        add_history_and_check_loop(&bender, &isLoop);
        move(&map, &bender); debug++;

        if (isLoop == 1)
        {
          state = LOOP;
          break;
        }
        if (get_map(bender.pos.line, bender.pos.ceil, &map) == FINISH)
        {
          state = END;
          break;
        }
        state = CHECK_MOVING;
        break;
      }
      case DIRECTION_CALC:
      {
        calc_direction(&map, &bender);
        dirCur = bender.direction;
        state = CHECK_MOVING;
        break;
      }
      case END:
      {
        // print history
        for (int i = 0; i < index; ++i)
        {
          switch (history[i].dir)
          {
            case SOUTH:
            {
              printf("SOUTH\n");
              break;
            }
            case WEST:
            {
              printf("WEST\n");
              break;
            }
            case NORTH:
            {
              printf("NORTH\n");
              break;
            }
            case EAST:
            {
              printf("EAST\n");
              break;
            }
          }
        }
        return 0;
      }
      case LOOP:
      {
        printf("LOOP\n");
        return 0;
      }
    }
  }

  return 0;
}
//-----------------------------------------------------------------------------
void calc_direction(sMapData *apMap, sBenderData *apBender)
{
  if (apBender->isInvert == 0)
  {
    switch (apBender->direction)
    {
    case SOUTH:
    {
      // checking EAST
      apBender->direction = EAST;
      if (is_move(apMap, apBender) == 1)
        return;

      // checking NORTH
      apBender->direction = NORTH;
      if (is_move(apMap, apBender) == 1)
        return;

      // checking WEST
      apBender->direction = WEST;
      if (is_move(apMap, apBender) == 1)
        return;

      apBender->direction = SOUTH;
      break;
    }
    case EAST:
    {
      // checking SOUTH
      apBender->direction = SOUTH;
      if (is_move(apMap, apBender) == 1)
        return;

      // checking NORTH
      apBender->direction = NORTH;
      if (is_move(apMap, apBender) == 1)
        return;

      // checking WEST
      apBender->direction = WEST;
      if (is_move(apMap, apBender) == 1)
        return;

      apBender->direction = EAST;
      break;
    }
    case NORTH:
    {
      // checking SOUTH
      apBender->direction = SOUTH;
      if (is_move(apMap, apBender) == 1)
        return;

      // checking EAST
      apBender->direction = EAST;
      if (is_move(apMap, apBender) == 1)
        return;

      // checking WEST
      apBender->direction = WEST;
      if (is_move(apMap, apBender) == 1)
        return;

      apBender->direction = NORTH;
      break;
    }
    case WEST:
    {
      // checking SOUTH
      apBender->direction = SOUTH;
      if (is_move(apMap, apBender) == 1)
        return;

      // checking EAST
      apBender->direction = EAST;
      if (is_move(apMap, apBender) == 1)
        return;

      // checking NORTH
      apBender->direction = NORTH;
      if (is_move(apMap, apBender) == 1)
        return;

      apBender->direction = WEST;
      break;
    }
    }
  }
  else
  {
    switch (apBender->direction)
    {
    case SOUTH:
    {
      // checking WEST
      apBender->direction = WEST;
      if (is_move(apMap, apBender) == 1)
        return;

      // checking NORTH
      apBender->direction = NORTH;
      if (is_move(apMap, apBender) == 1)
        return;

      // checking EAST
      apBender->direction = EAST;
      if (is_move(apMap, apBender) == 1)
        return;

      apBender->direction = SOUTH;
      break;
    }
    case EAST:
    {
      // checking WEST
      apBender->direction = WEST;
      if (is_move(apMap, apBender) == 1)
        return;

      // checking NORTH
      apBender->direction = NORTH;
      if (is_move(apMap, apBender) == 1)
        return;

      // checking SOUTH
      apBender->direction = SOUTH;
      if (is_move(apMap, apBender) == 1)
        return;

      apBender->direction = EAST;
      break;
    }
    case NORTH:
    {
      // checking WEST
      apBender->direction = WEST;
      if (is_move(apMap, apBender) == 1)
        return;

      // checking EAST
      apBender->direction = EAST;
      if (is_move(apMap, apBender) == 1)
        return;

      // checking SOUTH
      apBender->direction = SOUTH;
      if (is_move(apMap, apBender) == 1)
        return;

      apBender->direction = NORTH;
      break;
    }
    case WEST:
    {
      // checking NORTH
      apBender->direction = NORTH;
      if (is_move(apMap, apBender) == 1)
        return;

      // checking EAST
      apBender->direction = EAST;
      if (is_move(apMap, apBender) == 1)
        return;

      // checking SOUTH
      apBender->direction = SOUTH;
      if (is_move(apMap, apBender) == 1)
        return;

      apBender->direction = WEST;
      break;
    }
    }
  }
}
//-----------------------------------------------------------------------------
int is_equal(sHistory *apLeft, sHistory *apRight)
{
  if (apLeft->pos.ceil == apRight->pos.ceil &&
    apLeft->pos.line == apRight->pos.line)
    return 1;
  return 0;
}
//-----------------------------------------------------------------------------
void add_history_and_check_loop(sBenderData *apBender, int *apLoop)
{
  history[index].pos = apBender->pos;
  history[index].dir = apBender->direction;
  ++index;

  *apLoop = 0;

  int debug = 0;
  if (index == 47)
    debug = 0;

  int count_equals = 0;
  if (index >= 4)
  {
    int isLoop = 0;
    int lastI = index - 1;
    for (int i = index - 2; i >= 0; --i)
    {
      count_equals = 0;
      int li = lastI;
      int ci = i;

      for (int j = ci; j >= 0; --j)
      {
        if (is_equal(&history[li], &history[j]))
        {
          ci = j;
          break;
        }
      }

      for (; ci >= 0; --li, --ci)
      {
        if (is_equal(&history[li], &history[ci]))
          count_equals++;
        else
          count_equals = 0;

        if (count_equals >= 100)
        {
          *apLoop = 1;
          //debug = 0;
          return;
        }
      }
    }
  }
}
//-----------------------------------------------------------------------------
void move(sMapData *apMap, sBenderData *apBender)
{
  switch (apBender->direction)
  {
  case SOUTH:
  {
    apBender->pos.line++;
    break;
  }
  case EAST:
  {
    apBender->pos.ceil++;
    break;
  }
  case NORTH:
  {
    apBender->pos.line--;
    break;
  }
  case WEST:
  {
    apBender->pos.ceil--;
    break;
  }
  }

  eMap mapObj = get_map(apBender->pos.line, apBender->pos.ceil, apMap);

  switch (mapObj)
  {
  case WALL:       // '#'
  case EMPTY:      // ' '
  case FINISH:     // '$'
    return 0;
  case OBSTACLE:   // 'X'
  {
    set_map(apBender->pos.line, apBender->pos.ceil, apMap, EMPTY);
    break;
  }
  case S:          // 'S'
  {
    apBender->direction = SOUTH;
    break;
  }
  case E:          // 'E'
  {
    apBender->direction = EAST;
    break;
  }
  case N:          // 'N'
  {
    apBender->direction = NORTH;
    break;
  }
  case W:          // 'W'
  {
    apBender->direction = WEST;
    break;
  }
  case BEER:     // 'B'
  {
    if (apBender->isBeer)
      apBender->isBeer = 0;
    else
    {
      apBender->isBeer = 1;
      //set_map(apBender->pos.line, apBender->pos.ceil, apMap, EMPTY);
    }
    break;
  }
  case INVERT:     // 'I'
  {
    if (apBender->isInvert)
      apBender->isInvert = 0;
    else
      apBender->isInvert = 1;
    break;
  }
  case TELEPORT:   // 'T'
  {
    if (apBender->pos.line == apMap->teleportPos1.line &&
      apBender->pos.ceil == apMap->teleportPos1.ceil
      )
    {
      apBender->pos.line = apMap->teleportPos2.line;
      apBender->pos.ceil = apMap->teleportPos2.ceil;
    }
    else
    {
      apBender->pos.line = apMap->teleportPos1.line;
      apBender->pos.ceil = apMap->teleportPos1.ceil;
    }
    break;
  }
  }
}
//-----------------------------------------------------------------------------
int is_move(sMapData *apMap, sBenderData *apBender)
{
  int dl = 0;
  int dc = 0;

  switch (apBender->direction)
  {
  case SOUTH:
  {
    dl = 1;
    break;
  }
  case EAST:
  {
    dc = 1;
    break;
  }
  case NORTH:
  {
    dl = -1;
    break;
  }
  case WEST:
  {
    dc = -1;
    break;
  }
  }

  eMap mapObj = get_map(apBender->pos.line + dl, apBender->pos.ceil + dc, apMap);

  switch (mapObj)
  {
  case WALL:       // '#'
    return 0;
  case OBSTACLE:   // 'X'
  {
    if (apBender->isBeer)
      return 1;
    return 0;
  }
  case EMPTY:      // ' '
  case FINISH:     // '$'
  case S:          // 'S'
  case E:          // 'E'
  case N:          // 'N'
  case W:          // 'W'
  case INVERT:     // 'I'
  case TELEPORT:   // 'T'
  case BEER:       // 'B'
    return 1;
  }
  return 0;
}
//-----------------------------------------------------------------------------
void init_data(sBenderData *apBender, sMapData *apMap)
{
  apBender->direction = SOUTH;
  apBender->isBeer = 0;
  apBender->isInvert = 0;
  apBender->pos.ceil = -1;
  apBender->pos.line = -1;

  apMap->height = -1;
  apMap->width = -1;
  apMap->map = NULL;
  apMap->teleportPos1.ceil = -1;
  apMap->teleportPos1.line = -1;
  apMap->teleportPos2.ceil = -1;
  apMap->teleportPos2.line = -1;
}
//-----------------------------------------------------------------------------
eMap get_map(int aL, int aC, sMapData *apMap)
{
  return apMap->map[apMap->width*aL + aC];
}
//-----------------------------------------------------------------------------
void set_map(int aL, int aC, sMapData *apMap, eMap aValue)
{
  apMap->map[apMap->width*aL + aC] = aValue;
}
//-----------------------------------------------------------------------------
void load_map(sMapData *apMap, sBenderData *apBender)
{
  apMap->map = (eMap*)malloc((sizeof(eMap)) * apMap->height * apMap->width);

  for (int i = 0; i < apMap->height; i++)
  {
    for (int j = 0; j < apMap->width; j++)
    {
      switch (fgetc(stdin))
      {
      case ' ':
      {
        set_map(i, j, apMap, EMPTY);
        break;
      }
      case '#':
      {
        set_map(i, j, apMap, WALL);
        break;
      }
      case 'X':
      {
        set_map(i, j, apMap, OBSTACLE);
        break;
      }
      case '@':
      {
        set_map(i, j, apMap, EMPTY);
        apBender->pos.line = i;
        apBender->pos.ceil = j;
        break;
      }
      case '$':
      {
        set_map(i, j, apMap, FINISH);
        break;
      }
      case 'S':
      {
        set_map(i, j, apMap, S);
        break;
      }
      case 'E':
      {
        set_map(i, j, apMap, E);
        break;
      }
      case 'N':
      {
        set_map(i, j, apMap, N);
        break;
      }
      case 'W':
      {
        set_map(i, j, apMap, W);
        break;
      }
      case 'B':
      {
        set_map(i, j, apMap, BEER);
        break;
      }
      case 'I':
      {
        set_map(i, j, apMap, INVERT);
        break;
      }
      case 'T':
      {
        set_map(i, j, apMap, TELEPORT);

        if (apMap->teleportPos1.ceil == -1)
        {
          apMap->teleportPos1.line = i;
          apMap->teleportPos1.ceil = j;
        }
        else
          if (apMap->teleportPos2.ceil == -1)
          {
            apMap->teleportPos2.line = i;
            apMap->teleportPos2.ceil = j;
          }
        break;
      }
      }
    }
    char buff[10];
    fgets(buff, 10, stdin);
  }
}
//-----------------------------------------------------------------------------
void print_map(sMapData *apMap)
{
  for (int i = 0; i < apMap->height; i++)
  {
    for (int j = 0; j < apMap->width; j++)
    {
      switch (get_map(i, j, apMap))
      {
      case EMPTY:      // ' '
      {
        printf(" ");
        break;
      }
      case WALL:       // '#'
      {
        printf("#");
        break;
      }
      case OBSTACLE:   // 'X'
      {
        printf("X");
        break;
      }
      case FINISH:     // '$'
      {
        printf("$");
        break;
      }
      case S:          // 'S'
      {
        printf("S");
        break;
      }
      case E:          // 'E'
      {
        printf("E");
        break;
      }
      case N:          // 'N'
      {
        printf("N");
        break;
      }
      case W:          // 'W'
      {
        printf("W");
        break;
      }
      case BEER:       // 'B'
      {
        printf("B");
        break;
      }
      case INVERT:     // 'I'
      {
        printf("I");
        break;
      }
      case TELEPORT:   // 'T'
      {
        printf("T");
        break;
      }
      }
    }
    printf("\n");
  }
}


#endif // _MAIN_

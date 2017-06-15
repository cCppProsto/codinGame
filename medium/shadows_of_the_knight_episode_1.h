#ifndef _MAIN_
#define _MAIN_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//------------------------------------------------------------------------------
typedef struct
{
  float x;
  float y;
}sPos;

typedef struct
{
  int xLeft;
  int xRight;
  int yUp;
  int yDown;
}sRange;


/*
U  - (Up)
UR - (Up-Right)
R  - (Right)
DR - (Down-Right)
D  - (Down)
DL - (Down-Left)
L  - (Left)
UL - (Up-Left)
*/
typedef enum
{
  UNKNOWN = 0,
  U = 10,
  R = 2,
  D = 30,
  L = 4,
  UR = U + R, // 12
  DR = D + R, // 32
  DL = D + L, // 34
  UL = U + L  // 14
}eDirection;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
eDirection readDirection_stdin()
{
  eDirection res;
  char buffer[4];
  scanf("%s", buffer);

  fprintf(stderr, "pos = %s\n", buffer);

  switch (buffer[0])
  {
    case 'U':
    {
      res = U;
      break;
    }
    case 'R':
    {
      res = R;
      break;
    }
    case 'D':
    {
      res = D;
      break;
    }
    case 'L':
    {
      res = L;
      break;
    }
  }

  switch (buffer[1])
  {
    case 'U':
      return res = (eDirection)(res + U);
    case 'R':
      return res = (eDirection)(res + R);
    case 'D':
      return res = (eDirection)(res + D);
    case 'L':
      return res = (eDirection)(res + L);
  }
  return res;
}
//------------------------------------------------------------------------------
sRange calcRange(eDirection aDirection, sPos aCurPos, sRange aRect)
{
  sRange res;

  switch (aDirection)
  {
    case U:
    {
      res.xLeft = res.xRight = aCurPos.x;

      res.yUp   = aRect.yUp;
      res.yDown = aCurPos.y;
      break;
    }
    case R:
    {
      res.yDown = res.yUp = aCurPos.y;

      res.xLeft = aCurPos.x;
      res.xRight = aRect.xRight;
      break;
    }
    case D:
    {
      res.xLeft = res.xRight = aCurPos.x;

      res.yUp = aCurPos.y;
      res.yDown = aRect.yDown;
      break;
    }
    case L:
    {
      res.yDown = res.yUp = aCurPos.y;

      res.xLeft = aRect.xLeft;
      res.xRight = aCurPos.x;
      break;
    }
    case UR:
    {
      res.yUp   = aRect.yUp;
      res.yDown = aCurPos.y;

      res.xLeft = aCurPos.x;
      res.xRight = aRect.xRight;
      break;
    }
    case DR:
    {
      res.yUp = aCurPos.y;
      res.yDown = aRect.yDown;

      res.xLeft = aCurPos.x;
      res.xRight = aRect.xRight;
      break;
    }
    case DL:
    {
      res.yUp = aCurPos.y;
      res.yDown = aRect.yDown;

      res.xLeft = aRect.xLeft;
      res.xRight = aCurPos.x;
      break;
    }
    case UL:
    {
      res.xLeft = aRect.xLeft;
      res.xRight = aCurPos.x;

      res.yUp = aRect.yUp;
      res.yDown = aCurPos.y;
      break;
    }
  }

  return res;
}
//------------------------------------------------------------------------------
sPos calcPosition(sPos aCurPos, eDirection aDirection, sRange aRange)
{
  float x = aCurPos.x;
  float y = aCurPos.y;
  float dx;
  float dy;
  sPos res;

  switch (aDirection)
  {
    case U:
    {
      dx = 0.f;
      dy = (aRange.yUp - y) / 2.f;
      break;
    }
    case R:
    {
      dx = (aRange.xRight - x) / 2.f;
      dy = 0.f;
      break;
    }
    case D:
    {
      dx = 0.f;
      dy = (aRange.yDown - y) / 2.f;
      break;
    }
    case L:
    {
      dx = (aRange.xLeft - x) / 2.f;
      dy = 0.f;
      break;
    }
    case UR:
    {
      dx = (aRange.xRight - x) / 2.f;
      dy = (aRange.yUp - y) / 2.f;
      break;
    }
    case DR:
    {
      dx = (aRange.xRight - x) / 2.f;
      dy = (aRange.yDown - y) / 2.f;
      break;
    }
    case DL:
    {
      dx = (aRange.xLeft - x) / 2.f;
      dy = (aRange.yDown - y) / 2.f;
      break;
    }
    case UL:
    {
      dx = (aRange.xLeft - x) / 2.f;
      dy = (aRange.yUp - y) / 2.f;
      break;
    }
  }
  x += dx;
  y += dy;

  res.x = x;
  res.y = y;
  return res;
}
//------------------------------------------------------------------------------
int main()
{
  int         W;                  // width of the building.
  int         H;                  // height of the building.
  int         N;                  // maximum number of turns before game over.
  int         x;
  int         y;
  sPos        bmnCurPos;
  eDirection  direction;
  sRange      range = {0, 0, 0, 0};

  freopen("d:\\tmp\\codingame\\data.txt", "r", stdin);

  scanf("%d%d", &W, &H);
  scanf("%d", &N);
  scanf("%d%d", &x, &y);
  fgetc(stdin);

  bmnCurPos.x = x;
  bmnCurPos.y = y;
  range.xRight = W;
  range.yDown  = H;

  //fprintf(stderr, "w = %i, h = %i, n = %i\n", W, H, N);
  //fprintf(stderr, "x:%i, y:%i\n", bmnCurPos.x, bmnCurPos.y);

  while (1)
  {
    direction = readDirection_stdin();
    range     = calcRange(direction, bmnCurPos, range);

    bmnCurPos  = calcPosition(bmnCurPos, direction, range);

    printf("%i %i\n", (int)floor(bmnCurPos.x), (int)floor(bmnCurPos.y));
  }

  return 0;
}


#endif // _MAIN_

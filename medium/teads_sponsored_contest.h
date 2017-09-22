#ifndef _MAIN_
#define _MAIN_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
  int count;
  int pArray[10];
}node;

node array[150000] = {0};

typedef struct
{
  int level;
  int for_visit[10];
  int fvi;
}visit_info;


int depth_calc(int n)
{
  int f_v1[200000] = {0};
  int f_v2[200000] = {0};

  char visited[200000] = {0};

  int *pfvc = &f_v1[0];
  int fvsc = 0;

  int *pfvb = &f_v2[0];
  int fvib = 0;
  int fvsb = 0;
  int *tmp = NULL;

  int start_nv = n;

  visited[start_nv] = 1;
  for(int i = 0; i < array[start_nv].count; ++i)
  {
    pfvc[i] = array[start_nv].pArray[i];
    fvsc++;
  }

  int hours = 0;
  while(1)
  {
    hours++;
    for(int i = 0; i < fvsc; ++i)
    {
      if(visited[pfvc[i]] == 0)
      {
        visited[pfvc[i]] = 1;

        node *pn = &array[pfvc[i]];
        int end = pn->count;
        for(int j = 0; j < end; ++j)
        {
          if(visited[pn->pArray[j]] == 0)
          {
            pfvb[fvib] = pn->pArray[j];
            fvib++;
            fvsb++;
          }
        }
      }
    }

    tmp  = pfvc;
    pfvc = pfvb;
    pfvb = tmp;
    fvsc = fvsb;
    fvib = 0;
    fvsb = 0;

    if(fvsc == 0)
      break;
  }
  return hours;
}

int main()
{
  freopen("/home/ioleshko/tmp/teads_sponsored_contest_8.data", "r", stdin);

  int n; // the number of adjacency relations
  scanf("%d", &n);

  for (int i = 0; i < n; i++)
  {
    int xi; // the ID of a person which is adjacent to yi
    int yi; // the ID of a person which is adjacent to xi
    scanf("%d%d", &xi, &yi);

    array[xi].pArray[array[xi].count] = yi;
    array[yi].pArray[array[yi].count] = xi;
    array[xi].count++;
    array[yi].count++;
  }

  int hours = 0;
  for(int i = 0; i < n; ++i)
  {
    if(array[i].count == 1)
    {
      hours = depth_calc(i);
      break;
    }
  }

  if(hours & 0x01)
    hours++;
  hours /= 2;

  printf("%i\n", hours);
  return 0;
}

#endif // _MAIN_

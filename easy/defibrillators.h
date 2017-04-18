#ifndef _MAIN_
#define _MAIN_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define M_PI 3.1415926

char buffer_in[10000][300] = { {0}};
int end = 0;

int main()
{
  //freopen("d:\\data.txt", "r", stdin);

  char LON[51] = { 0 };
  char LAT[51] = { 0 };
  double a_latitude  = 0.0;
  double a_longitude = 0.0;
  int    i = 0;
  int    counter = 0;
  int    N = 0;
  int    N_I = 0;
  double d_min = 5000000.;
  int    d_pos = 0;

  scanf("%s", LON);
  for (i = 0; LON[i] != ','; ++i)
    ;
  LON[i] = '.';

  scanf("%s", LAT);
  for (i = 0; LAT[i] != ','; ++i)
    ;
  LAT[i] = '.';

  a_latitude = strtold(LAT, 0);
  a_longitude = strtold(LON, 0);

  // convert to radian
  a_latitude  = (M_PI * a_latitude) / 180.0;
  a_longitude = (M_PI * a_longitude) / 180.0;

  scanf("%d", &N); fgetc(stdin);

  while (N_I < N)
  {
    i = 0;
    fgets(buffer_in[N_I], 300, stdin);
    while (counter < 4)
    {
      if (buffer_in[N_I][++i] == ';')
        ++counter;
    }
    counter = 0;

    int index = 0;
    char t_lon[51] = { 0 };
    char t_lat[51] = { 0 };

    double b_longitude = 0.0;
    double b_latitude = 0.0;

    ++i;
    while (buffer_in[N_I][i] != ';')
    {
      if (buffer_in[N_I][i] == ',')
        t_lon[index] = '.';
      else
        t_lon[index] = buffer_in[N_I][i];
      ++i;
      ++index;
    }

    index = 0;
    ++i;
    while (buffer_in[N_I][i] != '\n' && buffer_in[N_I][i] != 0)
    {
      if (buffer_in[N_I][i] == ',')
        t_lat[index] = '.';
      else
        t_lat[index] = buffer_in[N_I][i];

      ++i;
      ++index;
    }

    b_longitude = strtold(t_lon, 0);
    b_latitude  = strtold(t_lat, 0);

    b_longitude = (b_longitude * M_PI) / 180.;
    b_latitude  = (b_latitude * M_PI)  / 180.;

    double x = 0.0;
    double y = 0.0;
    double d = 0.0;

    x = (b_longitude - a_longitude) * (cos((b_latitude + a_latitude)/2.));
    y = b_latitude - a_latitude;
    d = sqrt(x*x + y*y) * 6371.;

    if (d < d_min)
    {
      d_pos = N_I;
      d_min = d;
    }

    ++N_I;
  }

  i = 0;
  while (buffer_in[d_pos][i++] != ';')
    ;
  while (buffer_in[d_pos][i] != ';')
    putc(buffer_in[d_pos][i++], stdout);

  putc('\n', stdout);
  return 0;
}

/*
#define d2r (M_PI / 180.0)
double distance(double lat1, double long1, double lat2, double long2)
{
double dlong = (long2 - long1) * d2r;
double dlat = (lat2 - lat1) * d2r;
double a = pow(sin(dlat / 2.0), 2) + cos(lat1*d2r) * cos(lat2*d2r) * pow(sin(dlong / 2.0), 2);
double c = 2 * atan2(sqrt(a), sqrt(1 - a));
double d = 6367 * c;

return d;
}
 */


#endif // _MAIN_

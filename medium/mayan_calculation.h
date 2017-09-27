#ifndef _MAIN_
#define _MAIN_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


unsigned long degree_of_20 [] =
{
  1
 ,20
 ,400
 ,8000
 ,160000
 ,3200000
 ,64000000
 ,1280000000
 ,25600000000
 ,512000000000
 ,10240000000000
 ,204800000000000
 ,4096000000000000
 ,81920000000000000
};

int get_degree(unsigned long aValue)
{
  for(int i = 1; i < 9; ++i)
  {
    if(aValue < degree_of_20[i])
      return i-1;
  }
  return 0;
}


typedef struct
{
  char ascii_data[150];
  int  dec_value;
}numberInfo;

void read_nums(numberInfo *apOutNums,
               int *apNumWidth,
               int *apNumHeight,
               int *apNumAsciiSize)
{
  scanf("%d%d", apNumWidth, apNumHeight);

  while(getc(stdin) != '\n')
        ;

  int H = *apNumHeight;

  int numIndex = 0;
  int index    = 0;
  *apNumAsciiSize = (*apNumWidth * *apNumHeight) + 1;

  for(int i = 0; i < 20; ++i)
    apOutNums[i].dec_value = i;

  for (int i = 0; i < H; i++)
  {
    char ch = 0;
    while((ch = getc(stdin)) != '\n')
    {
      apOutNums[numIndex].ascii_data[*apNumWidth*i + index] = ch;
      index++;
      if(!(index % *apNumWidth))
      {
        numIndex++;
        index = 0;
      }
    }
    numIndex = 0;
  }
}

int get_digit_from_mayan(const char *apStr,
                         const numberInfo *apNums)
{
  for(int i = 0; i < 20; ++i)
  {
    if(strcmp(apStr, &(apNums[i].ascii_data[0])) == 0)
      return apNums[i].dec_value;
  }

  return 0;
}

int main()
{
  freopen("/home/ioleshko/tmp/mayan_calculation_12", "r", stdin);

  numberInfo mayanNums[20] = {0};

  int L;
  int H;
  int numAsciiSize = 0;

  read_nums(&mayanNums[0], &L, &H, &numAsciiSize);

  int S1;
  scanf("%d", &S1);

  int numbersDigitsFirst = S1 / H;
  unsigned long digitsFirst[20] = {0};
  int digit_f_i = 0;

  while(getc(stdin) != '\n')
        ;

  int index = 0;
  int line_n = 0;

  char *digit_val = (char*)calloc(0, numAsciiSize);

  for(int i = 0; i < numbersDigitsFirst; ++i)
  {
    char ch = 0;
    line_n  = 0;
    index   = 0;
    while(line_n != H)
    {
      ch = getc(stdin);
      if(ch == '\n')
        line_n++;
      else
      {
        digit_val[index] = ch;
        index++;
      }
    }
    digitsFirst[digit_f_i] = get_digit_from_mayan(&digit_val[0],
                                                  &mayanNums[0]);
    digit_f_i++;
  }


  int S2;
  scanf("%d", &S2);
  while(getc(stdin) != '\n')
        ;

  int numbersDigitsSecond = S2 / H;
  unsigned long digitsSecond[20] = {0};
  int digit_s_i = 0;

  index = 0;
  line_n = 0;

  for(int i = 0; i < numbersDigitsSecond; ++i)
  {
    char ch = 0;
    line_n  = 0;
    index   = 0;
    while(line_n != H)
    {
      ch = getc(stdin);
      if(ch == '\n')
        line_n++;
      else
      {
        digit_val[index] = ch;
        index++;
      }
    }
    digitsSecond[digit_s_i] = get_digit_from_mayan(&digit_val[0],
                                                  &mayanNums[0]);
    digit_s_i++;
  }

  unsigned long first = 0;
  unsigned long second = 0;

  for(int i = 0; i < numbersDigitsFirst; ++i)
    first += digitsFirst[i] * pow(20, (numbersDigitsFirst-1)-i);

  for(int i = 0; i < numbersDigitsSecond; ++i)
    second += digitsSecond[i] * pow(20, (numbersDigitsSecond-1)-i);

  char operation[2];
  scanf("%s", operation);

  long res = 0;

  switch(operation[0])
  {
    case '+':
    {
      res = first + second;
      break;
    }
    case '-':
    {
      res = first - second;
      break;
    }
    case '*':
    {
      res = first * second;
      break;
    }
    case '/':
    {
      res = first / second;
      break;
    }
  }

  int array_res[200] = {0};
  int array_res_size = 0;

  int           degree = 0;
  unsigned long tv1 = 0;
  unsigned long tv2 = 0;

  /*
  result = 148567923  = 2*(20^6) + 6*(20^5) + 8*(20^4) + 10*(20^3) + 19*(20^2) + 16*(20^1) + 3*(20^0)
  degree = 6
  20^6   = 64000000

  i1:
    degree = 6;
    tv1    = 64000000
    tv2    = 148567923 / 64000000 = 2.3214 = 2       !! 2*(20^6) !!
    result = 148567923 - (64000000*2) = 20567923

  i2:
    degree = 5;
    tv1    = 3200000
    tv2    = 20567923 / 3200000 = 6.4274  = 6        !! 6*(20^5) !!
    result = 20567923 - (3200000*6) = 1367923

  i3:
    degree = 4;
    tv1    = 160000
    tv2    = 1367923 / 160000 = 8.549                !! 8*(20^4) !!
    result = 1367923 - (160000 * 8) = 87923

  i4:
    degree = 3;
    tv1    = 8000
    tv2    = 87923 / 8000 = 10.9903                  !! 10*(20^3) !!
    result = 87923 - (8000 * 10) = 7923

  i5:
    degree = 2;
    tv1    = 400
    tv2    = 7923 / 400 = 19.8075                    !! 19*(20^2) !!
    result = 7923 - (400 * 19) = 323

  i6:
    degree = 1;
    tv1    = 20
    tv2    = 323 / 20 = 16.15                         !! 16*(20^1) !!
    result = 323 - (20 * 16) = 3

  i7:
    degree = 0;
    tv1    = 1
    tv2    = 3 / 20 = 0                               !! 3*(20^0) !!
  */

  degree = get_degree(res);
  while(degree >= 0)
  {
    tv1 = degree_of_20[degree];
    tv2 = res / tv1;
    res = res - degree_of_20[degree] * tv2;

    array_res[array_res_size] = tv2;
    array_res_size++;
    degree--;
  }

  int stack_i = 0;
  while(stack_i < array_res_size)
  {
    numberInfo *tmp = &(mayanNums[array_res[stack_i]]);
    for(int i = 0; i < L; ++i)
    {
      for(int j = 0; j < H; ++j)
        printf("%c", tmp->ascii_data[i*H + j]);
      printf("\n");
    }
    ++stack_i;
  }

  return 0;
}

#endif // _MAIN_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BALLS 3

#define TASTES 5

enum tastes
{
  C,
  N,
  V,
  P,
  F
};

int main(int argc, char **argv)
{
  int combi[200][TASTES];
  FILE *f = fopen("combinations.txt", "w");

  // num1 = C
  for (size_t i = 0; i < (size_t)pow(TASTES, BALLS); ++i)
  {
    for (size_t j = 0; j < TASTES; ++j)
    {
      for (size_t k = 0; k < TASTES; ++k)
      {
        combi[i][j] = k;
      }
      fprintf(f, "\n");
    }
  }

  printf("ok\n");

  switch (100)
  {
  case C:
    fprintf(f, "C");
    break;

  case N:
    fprintf(f, "N");
    break;

  case V:
    fprintf(f, "V");
    break;

  case F:
    fprintf(f, "F");
    break;

  case P:
    fprintf(f, "P");
    break;

  default:
    break;
  }

  fclose(f);
  return 0;
}
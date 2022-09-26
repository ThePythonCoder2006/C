#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <float.h>
#include <math.h>

double eval(double a, double b, double c, double x)
{
  return a * (x * x) + b * x + c;
}

int main(int argc, char **argv)
{
  if (!argc == 5)
  {
    fprintf(stderr, "[USAGE] sign_table.exe [output file] [a] [b] [c]");
    return EXIT_FAILURE;
  }

  --argc, ++argv; // removing the first arg (prog name)

  double a = atof(argv[0]);
  double b = atof(argv[1]);
  double c = atof(argv[2]);

  double r1, r2;

  double disc = b * b - 4 * a * c;

  printf("\t    x   \t| -oo \t (-%.2f - %csqrt(%.2f^2 - 4 * %.2f * %.2f))/(2 * %.2f) \t \t(-%.2f + %csqrt(%.2f^2 - 4 * %.2f * %.2f))/(2 * %.2f) \t +oo\n", b, disc < 0 ? 'i' : 0, b, a, c, a, b, disc < 0 ? 'i' : 0, b, a, c, a);
  printf("------------------------|-------------------------------------------------------------------------------------------------------------------------------------------\n");

  if (disc < 0)
  {
    printf("sign of f(x)            | \t\t\t\t\t\t\t\t\t%c \n", a >= 0 ? '+' : '-');
  }
  else
  {
    r1 = (-b + sqrt(disc)) / (2 * a);
    r2 = (-b - sqrt(disc)) / (2 * a);

    printf("sign of f(x)            |  %c   \t\t\t\t|\t\t\t\t\t%c  \t\t\t\t|\t\t\t\t   %c   \n", a >= 0 ? '+' : '-', a >= 0 ? '-' : '+', a >= 0 ? '+' : '-');
  }

  return EXIT_SUCCESS;
}
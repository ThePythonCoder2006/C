#include "stdio.h"
#include "stdlib.h"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    fprintf(stderr, "[ERROR] to many or not enought args provided ! (%i)\n", argc);
    exit(1);
  }

  int iter = atoi(argv[1]);

  printf("%i\n", iter);

  for (int i = 1; i <= iter; ++i)
  {
    if (i % 3 != 0 && i % 5 != 0)
      printf("%i", i);
    else
    {
      if (i % 3 == 0)
      {
        printf("fizz");
      }
      if (i % 5 == 0)
      {
        printf("buzz");
      }
    }

    printf("\n");
  }

  return 0;
}
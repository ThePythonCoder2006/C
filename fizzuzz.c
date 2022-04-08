#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int buffer = 0;

  if (argc < 2)
  {
    fprintf(stderr, "[ERROR] not enugth args ! (%i given)", argc - 1);
    exit(EXIT_FAILURE);
  }

#define ARGC argc
#if ARGC == 2
#endif
  // if (argc == 2)
  // {
  //   void out(char *s, ...)
  //   {
  //     va_list args;
  //     printf(s, args);
  //   }
  // }
  // if (argc == 3)
  // {
  //   FILE *f = fopen(argv[2], "w");
  //   void out(char *s, ...)
  //   {
  //     va_list args;
  //     fprintf(f, s, args);
  //   }

  //   void end(void)
  //   {
  //     fclose(f);
  //   }
  // }

  int iter = atoi(argv[1]);

  for (int i = 1; i <= iter; ++i)
  {
    if (i % 3 == 0)
    {
      printf("fizz");
      buffer = 1;
    }
    if (i % 5 == 0)
    {
      printf("buzz");
      buffer = 1;
    }

    if (!buffer)
    {
      printf("%i", i);
    }
    printf("\n");
    buffer = 0;
  }

  return 0;
}
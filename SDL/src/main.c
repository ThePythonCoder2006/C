#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

// compile:
// gcc src/main.c -o bin/main -I include -L lib -lmingw32 -lSDL2main -lSDL2

void ErrorExit(const char *message);

int main(int argc, char **argv)
{
  SDL_Window *window = NULL;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    ErrorExit("SDL initialization");
  }

  // Exe prog
  window = SDL_CreateWindow("window",
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            800, 600, 0);

  if (window == NULL)
  {
    ErrorExit("init window did not work");
  }

  SDL_Delay(5000);

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

void ErrorExit(const char *message)
{
  SDL_Log("[ERREUR] %s : %s", message, SDL_GetError());
  exit(EXIT_FAILURE);
}
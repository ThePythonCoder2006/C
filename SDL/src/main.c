#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

// Screen dimension constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Starts up SDL and creates window
bool init(void);

// Loads media
bool loadMedia(void);

// Frees media and shuts down SDL
void SDLclose(void);

// Loads individual image as texture
SDL_Texture *loadTexture(char *path);

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// The currently displayed texture
SDL_Texture *gTexture = NULL;

int main(int argc, char **argv)
{
	(void)argc, (void)argv;

	// Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
		return 1;
	}

	// Load media
	if (!loadMedia())
	{
		printf("Failed to load media!\n");
		return 1;
	}

	int mx, my;

	// Main loop flag
	bool quit = false;

	// Event handler
	SDL_Event e;

	// While application is running
	while (!quit)
	{
		// Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			// User requests quit
			if (e.type == SDL_QUIT)
				quit = true;
			// If mouse event happened
			if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
				// Get mouse position
				SDL_GetMouseState(&mx, &my);
		}

		// Clear screen
		SDL_RenderClear(gRenderer);

		// Display red circle texture
		SDL_Rect view_port = {.x = mx - 50, .y = my - 50, .w = 100, .h = 100};
		if (mx < 50)
			view_port.x = 0;

		if (my < 50)
			view_port.y = 0;

		if (mx > SCREEN_WIDTH - 50)
			view_port.x = SCREEN_WIDTH - 100;

		if (my > SCREEN_HEIGHT - 50)
			view_port.y = SCREEN_HEIGHT - 100;

		SDL_RenderSetViewport(gRenderer, &view_port);
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

		// Update screen
		SDL_RenderPresent(gRenderer);
	}

	// Free resources and close SDL
	SDLclose();

	return 0;
}

bool init(void)
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		printf("Warning: Linear texture filtering not enabled!");

	// Create window
	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL)
	{
		printf("Renderer could not be create! : %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);

	return true;
}

bool loadMedia(void)
{
	// Load PNG Surface
	gTexture = loadTexture("bin/circle.png");
	if (gTexture == NULL)
	{
		printf("failed to load PNG image!\n");
		return false;
	}

	return true;
}

void SDLclose(void)
{
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	// Destroy window
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture *loadTexture(char *path)
{
	// The final texture
	SDL_Texture *newTexture = NULL;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
		return false;
	}

	// Convert surface to screen format
	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	if (newTexture == NULL)
	{
		printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
		return false;
	}

	// Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	return newTexture;
}
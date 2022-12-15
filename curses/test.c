#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <inttypes.h>
#include <stdint.h>

#define WIDTH (100)
#define HEIGHT (100)

int main(int argc, char **argv)
{
	initscr();
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);

	for (uint16_t x = 0; x < WIDTH; ++x)
		for (uint16_t y = 0; y < HEIGHT; ++y)
			addch('x');

	mvchgat(1, 1, 1, 0, 1, NULL);

	refresh();

	scanw("%*c");

	return 0;
}
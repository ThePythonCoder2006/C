#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

typedef struct
{
	char type[2];
	uint8_t num;
} atom;

#define MAX_MOLECULE_SIZE 32
typedef struct
{
	atom type[MAX_MOLECULE_SIZE];
	uint8_t a_count; // the number of atoms in the molecule
	int8_t tot_charge;
	uint16_t coeff;
} comp;

#define MAX_EQ_SIZE 32
typedef struct
{
	comp react[MAX_EQ_SIZE],
			prod[MAX_EQ_SIZE];
} equa;

comp parse_comp(const char *restrict const stream);

int main(int argc, char **argv)
{
	(void)argc, argv;

	uint8_t react = 1; // are the comps getting read reagents
	for (uint8_t i = 0;; ++i)
	{
	}

	return 0;
}

comp parse_comp(const char *stream)
{
	comp mol;

	for (uint16_t i = 0; stream[i] != 0; ++i)
	{
		putchar(stream[i]);
	}

	return mol;
}
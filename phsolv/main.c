#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

// const char atoms_list[][3] = {"H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No", "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg"};

/*
0b00000000000000000000000000000000
	abcdefghijklmnopqrstuvwxyz
0b01100101101001110010111010000000
*/

#define ATOM_LIST_LETTER_OFFSET (32 - 26)
#define ATOM_LIST_SINGLE_LETTER_OFFSET (0)

const uint32_t atoms_list[26] = {
		/* */ /*abcdefghijklmnopqrstuvwxyz*/
		/*A*/ 0b00100010000110000111100000000000,
		/*B*/ 0b10001001101000000100000000000001,
		/*C*/ 0b10011100000110100110100000000001,
		/*D*/ 0b00010000000000000010000010000000,
		/*E*/ 0b00000000000000000110100000000000,
		/*F*/ 0b00001000000010000100000000000001,
		/*G*/ 0b10011000000000000000000000000000,
		/*H*/ 0b00001110000000100010000000000001,
		/*I*/ 0b00000000000001000100000000000001,
		/*J*/ 0b00000000000000000000000000000000,
		/*K*/ 0b00000000000000000100000000000001,
		/*L*/ 0b10000000100000000100100000000000,
		/*M*/ 0b00010010000001100001000000000000,
		/*N*/ 0b11001000100000110000000000000001,
		/*O*/ 0b00000000000000000010000000000001,
		/*P*/ 0b11010000000010100101100000000001,
		/*Q*/ 0b00000000000000000000000000000000,
		/*R*/ 0b11001111000001000000100000000000,
		/*S*/ 0b01101010100011000100000000000001,
		/*T*/ 0b11101001100110000000000000000000,
		/*U*/ 0b00000000000000000000000000000001,
		/*V*/ 0b00000000000000000000000000000001,
		/*W*/ 0b00000000000000000000000000000001,
		/*X*/ 0b00001000000000000000000000000000,
		/*Y*/ 0b01000000000000000000000000000001,
		/*Z*/ 0b00000000000001000100000000000000};

typedef struct
{
	char type[2];
	uint8_t num;
} atom;

#define MAX_MOLECULE_SIZE 64
#define MOLECULE_MAX_ATOM_COUNT 32
typedef struct
{
	char name[MAX_MOLECULE_SIZE]; // the name of the molecule (may not be the smallest form. ex : C2H5COOH)
	atom type[MOLECULE_MAX_ATOM_COUNT];
	uint8_t a_count; // the number of atoms in the molecule
	int8_t tot_charge;
	uint16_t coeff;
} molecule;
#define MOLECULE_ERROR                                        \
	(molecule)                                                  \
	{                                                           \
		.a_count = UINT8_MAX, .name = "ERROR", .coeff = UINT8_MAX \
	}

#define MAX_EQ_SIZE 32
typedef struct
{
	molecule react[MAX_EQ_SIZE],
			prod[MAX_EQ_SIZE];
} equa;

#define STRING_X(x) #x
#define STRINGIFY(x) STRING_X(x)

#define IS_UPPER(c) ((c) <= 'Z' && (c) >= 'A')
#define IS_LOWER(c) ((c) <= 'z' && (c) >= 'a')
#define IS_NOT_UPPER(c) ((c) > 'Z' || (c) < 'A')
#define IS_NOT_LOWER(c) ((c) > 'z' || (c) < 'a')

molecule parse_molecule(const char *restrict const stream);

int is_valid_atom(char atom[3]);

int main(int argc, char **argv)
{
	--argc, ++argv; // do not care about the program name

	printf("please write your unbalanced chemical equasion below :\n");

	// uint8_t react = 1; // are the comps getting read reagents
	char tmp;
	for (uint8_t i = 0;; ++i)
	{
		char buff[MAX_MOLECULE_SIZE];
		fscanf(stdin, "%" STRINGIFY(MAX_MOLECULE_SIZE) "s", buff);
		parse_molecule(buff);
		putchar('\n');
		if (fscanf(stdin, "%c", &tmp), tmp == '\n')
			break;
	}

	return 0;
}

molecule parse_molecule(const char stream[MAX_MOLECULE_SIZE])
{
	molecule mol = {.a_count = 0};
	char atom_type[3] = "\0\0\0";

	for (uint16_t i = 0; stream[i] != 0; ++mol.a_count, ++i)
	{
		if (IS_NOT_UPPER(stream[i]))
			return MOLECULE_ERROR;

		// the char is an uppercase letter

		if (IS_LOWER(stream[i + 1])) // the atom has a two letter name
		{
			if (!is_valid_atom(strncpy(atom_type, stream + i, 2)))
				return MOLECULE_ERROR;

			++i;

			// copy the atom type
			strncpy(mol.type[mol.a_count].type, atom_type, 2);
		}
		else
		{ // the atom has a one letter name
			if (!is_valid_atom(strncpy(atom_type, stream + i, 1)))
				return MOLECULE_ERROR;
				}

		// update the number of time the atom is present
		if (isdigit(stream[i + 1]))
		{
			++i;
			char num[MAX_MOLECULE_SIZE];
			const uint16_t start = i;
			while (isdigit(stream[i + 1]))
				++i;
			strncpy(num, stream + start, i - start + 1);
			num[i - start + 1] = 0; // add nul terminator

			mol.type[mol.a_count].num = atoi(num);
		}
		else
			mol.type[mol.a_count].num = 1;
	}

	return mol;
}

int is_valid_atom(char atom[3])
{
	// check if first char is an uppercase letter
	if (IS_NOT_UPPER(atom[0]))
		return 0;

	if (atom[1] == 0) // atom is one letter long
		return ((atoms_list[atom[0] - 'A'] >> ATOM_LIST_SINGLE_LETTER_OFFSET) & 1);

	// atom is two letters long
	// check if second char is a lowercase letter
	if (IS_NOT_LOWER(atom[1]))
		return 0;
	return ((atoms_list[atom[0] - 'A'] >> ((ATOM_LIST_LETTER_OFFSET) + 26 - (atom[1] - 'a') - 1)) & 1);
}
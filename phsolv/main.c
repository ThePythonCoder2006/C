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

typedef uint32_t atom_list[26];

#define ATOM_LIST_SINGLE_LETTER_OFFSET (0)

const atom_list atoms_list = {
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
	char type[3];
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
	uint8_t coeff;
} molecule;
#define MOLECULE_ERROR    \
	(molecule)              \
	{                       \
		.a_count = UINT8_MAX, \
		.name = "ERROR",      \
		.coeff = UINT8_MAX    \
	}

enum
{
	EQUA_PROD,
	EQUA_REACT,
};

#define MAX_EQ_SIZE 32
typedef struct
{
	molecule mols[2][MAX_EQ_SIZE];
	uint8_t counts[2];
	atom_list atoms_used;
} c_equa;
/*
a chemical equation :
mols[EQUA_REACT] is the reagent side of the equation
counts[EQUA_REACT] is the number of moelcules in the reagent side of the equation
the same with EQUA_PROD for the product side of the equation
*/

typedef struct
{
	uint32_t num, denom;
} ratio;

typedef struct
{
	ratio **coeff;
	uint8_t unkown_num;
} sys_eq;

#define STRING_X(x) #x
#define STRINGIFY(x) STRING_X(x)

#define IS_UPPER(c) ((c) <= 'Z' && (c) >= 'A')
#define IS_LOWER(c) ((c) <= 'z' && (c) >= 'a')
#define IS_NOT_UPPER(c) ((c) > 'Z' || (c) < 'A')
#define IS_NOT_LOWER(c) ((c) > 'z' || (c) < 'a')

molecule parse_molecule(const char *restrict const stream);

static inline int is_in_atom_list(const char atom[3], const atom_list list);
static inline int is_valid_atom(const char atom[3]);
int is_in_molecule(molecule molecule, char atom_type[3], uint8_t *id);
uint8_t get_multi_digit_number(const char *stream, uint8_t *num_len);
void print_molecule(const molecule mol);
void print_equa(c_equa c_equa);
c_equa solve_equa(c_equa eq);
sys_eq init_sys_equa(const uint8_t n);
void print_sys_eq(const sys_eq eq);

int main(int argc, char **argv)
{
	--argc, ++argv; // do not care about the program name

	printf("please write your unbalanced chemical equation below :\n");

	c_equa eq = {.counts = {0, 0}};

	uint8_t react = 1; // are the comps getting read reagents
	char tmp;
	for (uint8_t i = 0;; ++i)
	{
		char buff[MAX_MOLECULE_SIZE];
		fscanf(stdin, "%" STRINGIFY(MAX_MOLECULE_SIZE) "s", buff);
		if (buff[0] == '+')
			continue;

		if (buff[0] == '=')
		{
			react = 0;
			continue;
		}

		eq.mols[react][eq.counts[react]++] = parse_molecule(buff);

		if (fscanf(stdin, "%c", &tmp), tmp == '\n')
			break;
	}

	print_equa(eq);
	putchar('\n');

	const c_equa solved_equa = solve_equa(eq);

	print_equa(solved_equa);
	putchar('\n');

	return 0;
}

molecule parse_molecule(const char stream[MAX_MOLECULE_SIZE])
{
	molecule mol = {.a_count = 0, .coeff = 1}; // assume that there is one molecule, will be changed if necessary

	uint8_t start_offset = 0;

	if (isdigit(stream[0])) // there is a coefficiant before the molecule
	{
		uint8_t num, num_len;

		num = get_multi_digit_number(stream, &num_len);

		mol.coeff = num;
		start_offset = num_len;
	}

	strncpy(mol.name, stream + start_offset, strlen(stream));

	// parse the atoms
	for (uint16_t i = start_offset; stream[i] != 0; ++mol.a_count, ++i)
	{
		char atom_type[3] = "\0\0\0";
		uint8_t old, index;

		uint8_t num, num_len;

		if (IS_NOT_UPPER(stream[i]))
			return MOLECULE_ERROR;

		// the char is an uppercase letter
		if (IS_LOWER(stream[i + 1])) // the atom has a two letter name
		{
			if (!is_valid_atom(strncpy(atom_type, stream + i, 2)))
				return MOLECULE_ERROR;

			++i;

			// copy the atom type
			if ((old = is_in_molecule(mol, atom_type, &index)))
				--mol.a_count;
			else
			{
				mol.type[mol.a_count].type[0] = atom_type[0];
				mol.type[mol.a_count].type[1] = atom_type[1];
				mol.type[mol.a_count].type[2] = 0;
			}
		}
		else
		{ // the atom has a one letter name
			if (!is_valid_atom(strncpy(atom_type, stream + i, 1)))
				return MOLECULE_ERROR;

			// copy the atom type
			if ((old = is_in_molecule(mol, atom_type, &index)))
				--mol.a_count;
			else
			{
				mol.type[mol.a_count].type[0] = atom_type[0];
				mol.type[mol.a_count].type[1] = 0; // add the null terminator
			}
		}

		if (!isdigit(stream[i + 1])) // the atom has no digit after it, it is present a single time and has no charge
		{
			if (old)
				++mol.type[index].num;
			else
				mol.type[mol.a_count].num = 1;

			if (stream[i + 1] == '+' || stream[i + 1] == '-')
			{
				if (stream[i + 1] == '+')
					++mol.tot_charge;
				else
					--mol.tot_charge;
				++i;
			}
			continue;
		}

		num_len = 0;
		num = get_multi_digit_number(stream + i + 1, &num_len);
		i += num_len;

		if (stream[i + 1] != '+' && stream[i + 1] != '-') // start by atom count
		{
			if (old)
				mol.type[index].num += num;
			else
				mol.type[mol.a_count].num = num;

			if (stream[i + 1] != ',' && stream[i + 1] != '^') // if there are no charges
				continue;
			++i;

			if (!isdigit(stream[i + 1])) // there is a single charge (+ or -)
			{
				if (stream[i + 1] == '+')
					++mol.tot_charge;
				else
					--mol.tot_charge;
				++i;
				continue;
			}

			num = get_multi_digit_number(stream + i + 1, &num_len);
			i += num_len;

			if (stream[i + 1] != '+' && stream[i + 1] != '-')
				continue;

			if (stream[i + 1] == '+')
				mol.tot_charge += num;
			else
				mol.tot_charge -= num;
			i += 2;
		}
		else // multi digit charge without atom number (= only one atom)
		{
			if (stream[i + 1] == '+') // multi digit positive charge
				mol.tot_charge += num;
			else // multi digit negative charge
				mol.tot_charge -= num;
			++i;

			// set the atom count for this particular atom to one
			if (old)
				++mol.type[index].num;
			else
				mol.type[mol.a_count].num = 1;
		}
	}

	return mol;
}

static inline int is_in_atom_list(const char atom[3], const atom_list list)
{
	// check if first char is an uppercase letter
	if (IS_NOT_UPPER(atom[0]))
		return 0;

	if (atom[1] == 0) // atom is one letter long
		return ((list[atom[0] - 'A'] >> ATOM_LIST_SINGLE_LETTER_OFFSET) & 1);

	// atom is two letters long

	// check if second char is a lowercase letter
	if (IS_NOT_LOWER(atom[1]))
		return 0;

	return ((list[atom[0] - 'A'] >> (32 - (atom[1] - 'a') - 1)) & 1);
}

static inline int is_valid_atom(const char atom[3])
{
	// check if first char is an uppercase letter
	if (IS_NOT_UPPER(atom[0]))
		return 0;

	return is_in_atom_list(atom, atoms_list);
}

int is_in_molecule(molecule molecule, char atom_type[3], uint8_t *id)
{
	for (uint8_t i = 0; i < molecule.a_count; ++i)
		if (strcmp(molecule.type[i].type, atom_type) == 0) // if the two type are the same, the atom is already present
		{
			*id = i;
			return 1;
		}

	return 0;
}

uint8_t get_multi_digit_number(const char *stream, uint8_t *num_len)
{
	if (!isdigit(stream[0]))
		return 0;

	char num[MAX_MOLECULE_SIZE];
	uint8_t i = 0;
	while (isdigit(stream[i + 1]))
		++i;

	strncpy(num, stream, i + 1);
	num[i + 1] = 0; // add nul terminator

	*num_len = i + 1;

	return atoi(num);
}

void print_molecule(const molecule mol)
{

	printf("%" PRIu8, mol.coeff);
	for (uint8_t k = 0; k < mol.a_count; ++k)
		printf("%s%" PRIu8, mol.type[k].type, mol.type[k].num);

	if (mol.tot_charge != 0)
		printf(",%i%c", abs(mol.tot_charge), mol.tot_charge >= 0 ? '+' : '-');
	return;
}

void print_equa(c_equa equa)
{
	print_molecule(equa.mols[EQUA_REACT][0]);
	for (uint8_t i = 1; i < equa.counts[EQUA_REACT]; ++i)
	{
		printf(" + ");
		print_molecule(equa.mols[EQUA_REACT][i]);
	}

	printf(" => ");

	print_molecule(equa.mols[EQUA_PROD][0]);
	for (uint8_t i = 1; i < equa.counts[EQUA_PROD]; ++i)
	{
		printf(" + ");
		print_molecule(equa.mols[EQUA_PROD][i]);
	}

	return;
}

int is_solvable(c_equa eq)
{

	// listing all the atoms in the reagents
	for (uint8_t i = 0; i < eq.counts[EQUA_REACT]; ++i)
	{
		const molecule mol = eq.mols[EQUA_REACT][i];
		for (uint8_t j = 0; j < mol.a_count; ++j)
		{
			const atom atom = mol.type[j];
			if (atom.type[1] == 0) // the atom is single lettered
				eq.atoms_used[atom.type[0] - 'A'] |= 1 << ATOM_LIST_SINGLE_LETTER_OFFSET;
			else // the atom is multi lettered
				eq.atoms_used[atom.type[0] - 'A'] |= 1 << (32 - (atom.type[1] - 'a'));
		}
	}

	// checking if all the atoms present in the reagent are also present in the products
	for (uint8_t i = 0; i < eq.counts[EQUA_PROD]; ++i)
	{
		const molecule mol = eq.mols[EQUA_PROD][i];
		for (uint8_t j = 0; j < mol.a_count; ++j)
			if (!is_in_atom_list(mol.type[j].type, eq.atoms_used))
				return 0;
	}

	return 1;
}

sys_eq init_sys_equa(const uint8_t n)
{
	sys_eq eq = {.unkown_num = n};

	// n unknowns => n equations in the system
	eq.coeff = calloc(n, sizeof(ratio *));

	// n unknowns => n + 1 terms in each of the equations
	for (uint8_t i = 0; i < n; ++i)
		eq.coeff[i] = calloc(n + 1, sizeof(ratio));

	return eq;
}

void print_ratio(ratio val)
{
	if (val.denom == 0)
	{
		fprintf(stderr, "ERROR, division by zero !!!!\n");
		return;
	}

	if (val.denom == 1)
	{
		printf("%" PRIu8, val.num);
		return;
	}

	printf("%" PRIu8 "/%" PRIu8, val.num, val.denom);
	return;
}

void print_sys_eq(const sys_eq eq)
{
	for (uint8_t i = 0; i < eq.unkown_num; ++i)
	{
		for (uint8_t j = 0; j < eq.unkown_num; ++j)
		{
			print_ratio(eq.coeff[i][j]);
			printf(" + ");
		}
		print_ratio(eq.coeff[i][eq.unkown_num]);
		putchar('\n');
	}

	return;
}

void set_up_sys_equa_from_c_equa(sys_eq *s_eq, c_equa c_eq)
{
	for (uint8_t i = 0; i < s_eq->unkown_num; ++i)
	{
	}

	return;
}

// solving the chemical equation by substitution
c_equa solve_equa(c_equa eq)
{
	if (!is_solvable(eq))
	{
		fprintf(stderr, "the equation cannot be solved !!!\n");
		return eq;
	}

	sys_eq syst = init_sys_equa(eq.counts[EQUA_PROD] + eq.counts[EQUA_REACT]);

	set_up_sys_equa_from_c_equa(&syst, eq);

	print_sys_eq(syst);

	return eq;
}
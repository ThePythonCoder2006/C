#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <mpfr.h>

// GO TO DIR:
//     cd C:/Users/Elève/Desktop/document/progra/C/pi
// or  cd C:/Users/paul/Desktop/documents/programation/C/pi

// COMPILE:
//   gcc hex.c -o main -lmpfr -lgmp

// RUN :
//   ./main

//--------------------------------------------------------------------------------------------

#define DIGITS 1000000

#define CONV 3.321928

#define PREC DIGITS *CONV

//--------------------------------------------------------------------------------------------

int main(void)
{
	mpfr_t a0;
	mpfr_init2(a0, PREC);

	mpfr_set_ui(a0, 1, MPFR_RNDN);

	mpfr_div_ui(a0, a0, 3, 0);

	mpfr_clear(a0);
	return 0;
}

//--------------------------------------------------------------------------------------------
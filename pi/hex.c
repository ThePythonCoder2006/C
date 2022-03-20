#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <mpfr.h>

// GO TO DIR:
//     cd C:/Users/Elève/Desktop/document/progra/C/pi
// or  cd C:/Users/paul/Desktop/documents/programation/C/pi

// COMPILE:
//   gcc *.c -o main -lmpfr -lgmp

// RUN :
//   ./main

//--------------------------------------------------------------------------------------------

#define PREC 10 * 1024

//--------------------------------------------------------------------------------------------

int main(void)
{
	mpfr_t third;
	mpfr_init2(third, PREC);

	mpfr_set_ui(third, 1, MPFR_RNDN);

	mpfr_div_ui(third, third, 3, MPFR_RNDN);

	mpfr_out_str(stdout, 10, 0, third, 0);

	mpfr_clear(third);
	return 0;
}

//--------------------------------------------------------------------------------------------
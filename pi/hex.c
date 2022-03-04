#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "c_mpq.h"
#include "c_mpf.h"

#include <mpir.h>

//GO TO DIR:
//    cd C:/Users/Elève/Desktop/document/progra/C/pi
//or  cd C:/Users/paul/Desktop/document/programation/C/pi

//COMPILE:
//  gcc *.c -o main -lmpir

//RUN :
//  ./main

//--------------------------------------------------------------------------------------------

#define PREC 10 * 1024

//--------------------------------------------------------------------------------------------

int main(void)
{
	mpq_t sqrt2;
	mpq_init_set_str(sqrt2, "2", 10);
	mpq_sqrt(sqrt2, sqrt2, PREC);

	mpq_t a0;
	mpq_init_set_str(a0, "1/3", 10);

	mpq_t s1x;
	mpq_init(s1x);

	mpq_snx(s1x, 1, PREC);

	printf("PI: "); mpq_dec_out_str(stdout, 10, PREC, a0); printf("\n");

	mpq_clear(a0);

	FILE *f = fopen("out.txt", "w");

	fclose(f);
}

//--------------------------------------------------------------------------------------------
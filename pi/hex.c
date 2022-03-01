#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "c_mpq.h"
#include "c_mpf.h"

#include <mpir.h>

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

	mpq_t s1;
	mpq_init(s1);
	mpq_set(s1, sqrt2);
	mpq_sub_ui(s1, s1, 1);

	mpq_t s1x;
	mpq_init(s1x);

	mpq_snx(s1x, 1);

	printf("PI: "); mpq_dec_out_str(stdout, 10, PREC, s1); printf("\n");

	mpq_clear(a0);
	mpq_clear(s1);

	FILE *f = fopen("out.txt", "w");

	mpq_dec_out_str(f, 10, PREC, s1);

	fclose(f);
}

//--------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "c_mpq.h"
#include "c_mpf.h"

#include <mpir.h>

//--------------------------------------------------------------------------------------------

#define PREC 1024

//--------------------------------------------------------------------------------------------

int main(void)
{
	printf("ok\n");

	FILE *f = fopen("out.txt", "w");

	mpq_t a0;
	mpq_init_set_str(a0, "1/80", 10);

	mpf_t e;
	mpf_init2(e, PREC);

	mpq_sqrt(a0, a0);

  mpf_set_q(e, a0);

	printf("PI: "); mpf_out_str(stdout, 10, 0, e); printf("\n");

	mpq_clear(a0);
	mpf_clear(e);

	fclose(f);
}

//--------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <mpir.h>

void mpf_qtrt(mpf_t rop, mpf_t op);

int mpq_init_set_str(mpq_t rop, char *str, int base);

void mpq_sqrt(mpq_t rop, mpq_t op);

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

int mpq_get_num_to_mpf(mpf_t rop, mpq_t op)
{
	mpf_t num;
	mpf_init(num);

	size_t num_size = mpz_sizeinbase(mpq_numref(op), 10);

	char *num_str;
	num_str = malloc(sizeof(char) * (num_size + 5));

	if (num_str == NULL)
	{
		fprintf(stderr, "error append with dynamic allocating : %i", errno);
		return -1;
	}
	mpz_get_str(num_str, 10, mpq_numref(op));

	mpf_set_str(num, num_str, 10);

	free(num_str);

	mpf_clear(num);

	return 0;
}

int mpq_get_den_to_mpf(mpf_t rop, mpq_t op)
{
	mpf_t den;
	mpf_init(den);
	
	size_t den_size = mpz_sizeinbase(mpq_denref(op), 10);

	char *den_str;
	den_str = malloc(sizeof(char) * (den_size + 5));

	if (den_str == NULL)
	{
		fprintf(stderr, "error append with dynamic allocating : %i", errno);
		return -1;
	}
	mpz_get_str(den_str, 10, mpq_denref(op));
	
	mpf_set_str(den, den_str, 10);

	free(den_str);

	mpf_clear(den);
	return 0;
}

void mpf_qtrt(mpf_t rop, mpf_t op)
{
	mpf_sqrt(rop, op);
	mpf_sqrt(rop, rop);
}

int mpq_init_set_str(mpq_t rop, char *str, int base)
{
	mpq_init(rop);
	return mpq_set_str(rop, str, base);
}

void mpq_sqrt(mpq_t rop, mpq_t op)
{
	mpf_t q;
	mpf_init(q);
	mpf_set_q(q, op);

	mpf_sqrt(q, q);

	mpq_set_f(rop, q);

	mpf_clear(q);
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <mpir.h>

int mpq_get_num_to_mpf(mpf_t rop, mpq_t op);

int mpq_get_den_to_mpf(mpf_t rop, mpq_t op);

int mpq_to_mpf(mpf_t rop, mpq_t op);

void mpf_qtrt(mpf_t rop, mpf_t op);

int mpq_init_set_str(mpq_t rop, char *str, int base);

void mpq_sqrt(mpq_t rop, mpq_t op);

//--------------------------------------------------------------------------------------------

int main(void)
{
	printf("ok\n");

	FILE *f = fopen("out.txt", "w");

	mpq_t a0;
	mpq_init_set_str(a0, "1/9", 10);

	mpf_t e;
	mpf_init2(e, 1024);

	//mpq_sqrt(a0, a0);

	int ret = mpq_to_mpf(e, a0);
	if (ret != 0)	exit(EXIT_FAILURE);

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

int mpq_to_mpf(mpf_t rop, mpq_t op)
{
	mpf_t num, den;
	mpf_init(num);
	mpf_init(den);

	int ret1 = mpq_get_num_to_mpf(num, op);
	int ret2 = mpq_get_den_to_mpf(den, op);

	if (ret1 || ret2) return -1;

	mpf_div(rop, num, den);

	mpf_clear(num);
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
	mpz_t num;
	mpz_t den;
	mpz_init(num);
	mpz_init(den);

	//mpz_set(num, mpq_numref(op));
	//mpz_set(den, mpq_denref(op));

	//mpz_sqrt(num, num);
	//mpz_sqrt(den, den);

	printf("ok\n");

	//mpq_set_num(rop, num);
	//mpq_set_den(rop, den);

	(void) rop;

	mpz_clear(num);
	mpz_clear(den);
}
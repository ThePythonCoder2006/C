#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>

int mpq_to_mpf(mpf_t rop, mpq_t ratio);

int main(void)
{
	FILE *f = fopen("out.txt", "w");

	mpq_t a0;
	mpq_init(a0);
	mpq_set_str(a0, "1/3", 10);

	mpf_t e;
	mpf_init2(e, 1024);

	mpq_to_mpf(e, a0);

	printf("Hello, MPIR: "); mpq_out_str(stdout, 10, a0); printf("\n");
	printf("PI: "); mpf_out_str(stdout, 10, 0, e);

	mpq_clear(a0);
	mpf_clear(e);

	fclose(f);
}

int mpq_to_mpf(mpf_t rop, mpq_t ratio)
{
	mpf_t den;
	mpf_t num;

	size_t num_size = mpz_sizeinbase(mpq_numref(ratio), 10);
	size_t den_size = mpz_sizeinbase(mpq_denref(ratio), 10);

	char *num_str;
	num_str = malloc(num_size);
	mpz_get_str(num_str, 10, mpq_numref(ratio));

	char *den_str;
	den_str = malloc(den_size);
	mpz_get_str(den_str, 10, mpq_denref(ratio));

	mpf_set_str(den, den_str, 10);
	mpf_set_str(num, num_str, 10);

	mpf_div(rop, den, num);

	mpf_clear(den);
	mpf_clear(num);

	free(num_str);
	free(den_str);
	return 0;
}
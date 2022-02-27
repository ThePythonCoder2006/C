#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>

int mpq_to_mpf(mpf_t rop, mpq_t ratio);

int main(void)
{
	printf("ok\n");
	FILE *f = fopen("out.txt", "w");

	mpq_t a0;
	mpq_init(a0);
	mpq_set_str(a0, "1/3", 10);

	mpf_t e;
	mpf_init2(e, 1024);
	printf("ok\n");

	int ret = mpq_to_mpf(e, a0);
	printf("ok\n");

	if (ret != 0)
	{
		exit(EXIT_FAILURE);
	}

	printf("Hello, MPIR: "); mpq_out_str(stdout, 10, a0); printf("\n");
	printf("PI: "); mpf_out_str(stdout, 10, 0, e); printf("\n");

	mpq_clear(a0);
	mpf_clear(e);

	fclose(f);
}

int mpq_to_mpf(mpf_t rop, mpq_t ratio)
{
	mpf_t den;
	mpf_t num;

	mpf_init(den);
	mpf_init(num);

	size_t num_size = mpz_sizeinbase(mpq_numref(ratio), 10);
	size_t den_size = mpz_sizeinbase(mpq_denref(ratio), 10);

	char *num_str;
	num_str = malloc(sizeof(char) * num_size + 10);
	mpz_get_str(num_str, 10, mpq_numref(ratio));

	char *den_str;
	den_str = malloc(sizeof(char) * den_size + 10);
	mpz_get_str(den_str, 10, mpq_denref(ratio));

	mpf_set_str(den, den_str, 10);
	mpf_set_str(num, num_str, 10);

	mpf_div(rop, num, den);

	free(num_str);
	free(den_str);

	mpf_clear(den);
	mpf_clear(num);
	return 0;
}
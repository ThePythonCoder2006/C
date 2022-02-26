#include <stdio.h>
#include <mpir.h>

int main(void)
{
	mpz_t a, b, c;
	mpz_init(a);
	mpz_init(b);
	mpz_init(c);

	mpq_t d;
	mpq_init(d);
	mpq_set_str(d, "1/3", 10);

	mpf_t tmp1, tmp2;
	mpf_init(tmp1);
	mpf_init(tmp2);

	mpf_t e;
	mpf_init(e);

	char *tmp1_str;
	mpz_get_str(tmp1_str, 10, mpq_numref(d));

	char *tmp2_str;
	mpz_get_str(tmp2_str, 10, mpq_numref(d));

	mpf_set_str(tmp1, tmp1_str, 10);
	mpf_set_str(tmp2, tmp2_str, 10);

	mpf_div(e, tmp1, tmp2);

	mpz_set_str(a, "1", 10);
	mpz_set_str(b, "2", 10);
	mpz_add(c, a, b);
	printf("Hello, MPIR: "); mpz_out_str(stdout, 10, c); printf("\n");
	printf("PI: "); mpf_out_str(stdout, 10, 0, e);

	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(c);
	mpq_clear(d);
	mpf_clear(e);
	mpf_clear(tmp1);
	mpf_clear(tmp2);
}
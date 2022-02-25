#include <stdio.h>
#include <mpir.h>

int main(void)
{
	mpz_t a, b, c;
	mpz_init(a);
	mpz_init(b);
	mpz_init(c);
	mpz_set_str(a, "1", 10);
	mpz_set_str(b, "2", 10);
	mpz_add(c, a, b);
	printf("Hello, MPIR: %i", c);
}

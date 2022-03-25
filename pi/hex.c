#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

#include <mpfr.h>

// GO TO DIR:
//     cd C:/Users/Elève/Desktop/document/progra/C/pi
// or  cd C:/Users/paul/Desktop/documents/programation/C/pi

// COMPILE:
//   gcc hex.c -o main -lmpfr -lgmp

// RUN :
//   ./main

//--------------------------------------------------------------------------------------------

void mpfr_list_init2(const int prec, mpfr_t list[], size_t size);
void mpfr_list_clear(mpfr_t list[], size_t size);

void mpfr_qtrt(mpfr_t rop, mpfr_t op, mpfr_rnd_t round);
void mpfr_snx_init();
void mpfr_sn(mpfr_t rop, int n, mpfr_prec_t prec, mpfr_rnd_t round);
void mpfr_snx(mpfr_t rop, int n, mpfr_prec_t prec, mpfr_rnd_t round);
void mpfr_an(mpfr_t rop, int n, mpfr_prec_t prec, mpfr_rnd_t round);

//--------------------------------------------------------------------------------------------

#define DIGITS 1000

#define CONV 3.321928

#define PREC (DIGITS * CONV)

#define ITER 5

#define CACHE (ITER + 1)

//--------------------------------------------------------------------------------------------

mpfr_t sn_c[CACHE];
mpfr_t snx_c[CACHE];
mpfr_t an_c[CACHE];

int main(void)
{
	mpq_t a0;
	mpq_init(a0);
	mpq_set_ui(a0, 1, 3);

	//----------------------------------
	mpfr_list_init2(PREC, sn_c, CACHE);

	// init s1
	mpfr_sqrt_ui(sn_c[0], 2, 0);
	mpfr_sub_ui(sn_c[0], sn_c[0], 1, 0);

	//----------------------------------
	mpfr_list_init2(PREC, snx_c, CACHE);

	mpfr_sn(sn_c[3], 3, PREC, 0);

	//----------------------------------
	mpfr_list_init2(PREC, an_c, CACHE);

	mpfr_set_q(an_c[0], a0, 0);

	printf("\n");
	mpfr_out_str(stdout, 10, 0, sn_c[0], 0);
	printf("\n");
	printf("\n");

	mpq_clear(a0);
	mpfr_list_clear(sn_c, CACHE);
	mpfr_list_clear(snx_c, CACHE);
	mpfr_list_clear(an_c, CACHE);
	return 0;
}

//--------------------------------------------------------------------------------------------

void mpfr_list_init2(const int prec, mpfr_t list[], size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		mpfr_init2(list[i], prec);
	}
}

void mpfr_list_clear(mpfr_t list[], size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		mpfr_clear(list[i]);
	}
}

void mpfr_qtrt(mpfr_t rop, mpfr_t op, mpfr_rnd_t round)
{
	mpfr_rootn_ui(rop, op, 4, round);
}

void mpfr_sn(mpfr_t rop, int n, mpfr_prec_t prec, mpfr_rnd_t round)
{
	assert(n <= ITER);
	if (mpfr_nan_p(sn_c[n]) != 0)
	{
		printf("(sn) n: %i\n", n);
		assert(n > 0);

		// consts --------------
		mpfr_t snx;
		mpfr_init2(snx, prec);
		mpfr_snx(snx, n - 1, prec, round);

		printf("ok\n");

		mpfr_t u;
		mpfr_init2(u, prec);
		mpfr_sqr(u, snx, round);
		mpfr_add_ui(u, u, 1, round);
		mpfr_mul(u, u, snx, round);
		mpfr_mul_ui(u, u, 8, round);
		mpfr_qtrt(u, u, round);

		mpfr_t t;
		mpfr_init2(t, prec);
		mpfr_add_ui(t, snx, 1, round);

		mpfr_printf("snx: %.60Rf\nu: %.60Rf\n", snx, u);

		//--------------

		mpfr_ui_sub(sn_c[n], 1, snx, round);
		mpfr_pow_ui(sn_c[n], sn_c[n], 4, round);

		mpfr_t mul, tmp;
		mpfr_inits2(prec, mul, tmp, (mpfr_ptr)0);

		mpfr_add(mul, t, u, round);
		mpfr_sqr(mul, mul, round);
		mpfr_div(sn_c[n], sn_c[n], mul, round);

		mpfr_sqr(tmp, u, round);
		mpfr_sqr(mul, t, round);
		mpfr_add(mul, mul, tmp, round);

		mpfr_div(sn_c[n], sn_c[n], mul, round);

		mpfr_clears(mul, tmp, (mpfr_ptr)0);

		//--------------
		mpfr_clear(snx);
		mpfr_clear(u);
		mpfr_clear(t);
	}
	mpfr_set(rop, sn_c[n], round);
}

void mpfr_snx(mpfr_t rop, int n, mpfr_prec_t prec, mpfr_rnd_t round)
{
	assert(n <= ITER);
	if (mpfr_nan_p(snx_c[n]) != 0)
	{
		printf("(snx) n: %i\n", n);
		assert(n >= 0);
		mpfr_sn(snx_c[n], n, prec, round);
		mpfr_pow_ui(snx_c[n], snx_c[n], 4, round);
		mpfr_ui_sub(snx_c[n], 1, snx_c[n], round);
		mpfr_qtrt(snx_c[n], snx_c[n], round);
	}
	mpfr_set(rop, snx_c[n], round);
}

void mpfr_an(mpfr_t rop, int n, mpfr_prec_t prec, mpfr_rnd_t round)
{
	assert(n <= ITER);
	if (mpfr_nan_p(snx_c[n]) != 0)
	{
		printf("(an) n: %i\n", n);
		assert(n > 0);

		mpfr_t sn;
		mpfr_init2(sn, prec);

		mpfr_t t, m1, m2;
		mpfr_inits2(prec, t, m1, m2, (mpfr_ptr)0);

		mpfr_t tmp;
		mpfr_init2(tmp, prec);

		mpfr_mul_ui();

		mpfr_clear(sn);
		mpfr_clear(tmp);
		mpfr_clears(t, m1, m2, (mpfr_ptr)0);
	}
	mpfr_set(rop, an_c[n], round);
}
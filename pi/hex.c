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
void mpfr_sn_init();
void mpfr_snx_init();
void mpfr_sn(mpfr_t rop, int n, const int prec, mpfr_rnd_t round);
void mpfr_snx(mpfr_t rop, int n, const int prec, mpfr_rnd_t round);
void mpfr_an(mpfr_t rop, int n, const int prec, mpfr_rnd_t round);

//--------------------------------------------------------------------------------------------

#define DIGITS 100

#define CONV 3.321928

#define PREC (DIGITS * CONV)

#define ITER 3

#define CACHE (ITER + 1)

//--------------------------------------------------------------------------------------------

mpfr_t sn_cache[ITER];
mpfr_t snx_cache[ITER];

int main(void)
{
	mpq_t a0;
	mpq_init(a0);
	mpq_set_ui(a0, 1, 3);

	mpfr_sn_init();

	mpfr_sqrt_ui(sn_cache[0], 2, 0);
	mpfr_sub_ui(sn_cache[0], sn_cache[0], 1, 0);

	mpfr_snx_init();

	mpfr_snx(snx_cache[0], 0, PREC, 0);

	mpq_out_str(stdout, 10, a0);
	printf("\n");
	mpfr_out_str(stdout, 10, 0, sn_cache[0], 0);
	printf("\n");
	mpfr_out_str(stdout, 10, 0, snx_cache[0], 0);

	mpq_clear(a0);
	mpfr_list_clear(sn_cache, ITER);
	mpfr_list_clear(snx_cache, ITER);
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

void mpfr_sn_init()
{
	mpfr_list_init2(PREC, sn_cache, ITER);
}

void mpfr_snx_init()
{
	mpfr_list_init2(PREC, snx_cache, ITER);
}

void mpfr_sn(mpfr_t rop, int n, const int prec, mpfr_rnd_t round)
{
	assert(n <= ITER);
	if (mpfr_nan_p(sn_cache[n]) != 0)
	{
		assert(n > 0);

		// consts --------------
		mpfr_t snx;
		mpfr_init2(snx, prec);
		mpfr_snx(snx, n - 1, prec, round);

		mpfr_t u;
		mpfr_init2(u, prec);
		mpfr_pow_ui(u, snx, 2, round);
		mpfr_add_ui(u, u, 1, round);
		mpfr_mul(u, u, snx, round);
		mpfr_mul_ui(u, u, 8, round);
		mpfr_qtrt(u, u, round);

		//--------------

		mpfr_add_ui(snx_cache[n], snx, 1, round);
		mpfr_add(snx_cache[n], snx_cache[n], u, round);
		mpfr_sqr(snx_cache[n], snx_cache[n], round);

		mpfr_t mul, tmp;
		mpfr_inits2(prec, mul, tmp, (mpfr_ptr)0);

		mpfr_add_ui(mul, snx, 1, round);
		mpfr_sqr(mul, mul, round);
		mpfr_sqr(tmp, u, round);
		mpfr_add(tmp, tmp, mul, round);
		mpfr_mul(snx_cache[n], snx_cache[n], tmp, round);

		mpfr_add_ui(mul, snx, 1, round);
		mpfr_pow_ui(mul, mul, 4, round);

		mpfr_div(snx_cache[n], mul, snx_cache[n], round);

		mpfr_clears(mul, tmp, (mpfr_ptr)0);

		//--------------
		mpfr_clear(snx);
		mpfr_clear(u);
	}
	mpfr_set(rop, sn_cache[n], round);
}

void mpfr_snx(mpfr_t rop, int n, const int prec, mpfr_rnd_t round)
{
	assert(n <= ITER);
	if (mpfr_nan_p(snx_cache[n]) != 0)
	{
		mpfr_sn(snx_cache[n], n, prec, round);
		mpfr_pow_ui(snx_cache[n], snx_cache[n], 4, round);
		mpfr_ui_sub(snx_cache[n], 1, snx_cache[n], round);
		mpfr_qtrt(snx_cache[n], snx_cache[n], round);
	}
	mpfr_set(rop, snx_cache[n], round);
}
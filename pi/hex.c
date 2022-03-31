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

#define DIGITS 1100

#define CONV 3.321928

#define PREC (DIGITS * CONV)

#define ITER 3

//--------------------------------------------------------------------------------------------

mpfr_t buffer;

mpfr_t sn, snx, an;
mpfr_t sn_p, snx_p, an_p;

mpq_t a0;
mpfr_t s1;

int main(void)
{
	mpq_init(a0);
	mpq_set_ui(a0, 1, 3);

	mpfr_inits2(PREC, sn, snx, an, (mpfr_ptr)0);
	mpfr_inits2(PREC, sn_p, snx_p, an_p, (mpfr_ptr)0);
	mpfr_init2(s1, PREC);

	mpfr_t pi;
	mpfr_init2(pi, PREC);

	//----------------------------------
	mpfr_init2(sn, PREC);

	// init s1
	mpfr_sqrt_ui(s1, 2, 0);
	mpfr_sub_ui(s1, s1, 1, 0);

	// mpfr_sn(sn, 1, PREC, 0);
	// mpfr_snx(snx, 1, PREC, 0);

	//----------------------------------

	mpfr_set_q(an, a0, 0);

	mpfr_an(an, 1, PREC, 0);

	mpfr_ui_div(pi, 1, an, 0);

	mpfr_printf("\nsn: %.60Rf\nsnx: %.60Rf", sn, snx);

	FILE *out = fopen("pi-out.txt", "w");

	mpfr_fprintf(out, "%.1100Rf\n", pi);

	fclose(out);

	mpq_clear(a0);
	mpfr_clear(pi);
	mpfr_clears(sn, snx, an, (mpfr_ptr)0);
	mpfr_clears(sn_p, snx_p, an_p, (mpfr_ptr)0);
	mpfr_clear(s1);
	mpfr_free_cache();
	return 0;
}

//--------------------------------------------------------------------------------------------

void mpfr_qtrt(mpfr_t rop, mpfr_t op, mpfr_rnd_t round)
{
	mpfr_rootn_ui(rop, op, 4, round);
}

void mpfr_sn(mpfr_t rop, int n, mpfr_prec_t prec, mpfr_rnd_t round)
{
	assert(n <= ITER);
	assert(n >= -20);

	printf("(sn) n: %i\n", n);

	if (n <= 1)
	{
		mpfr_set(rop, s1, round);
		return;
	}

	mpfr_swap(sn, sn_p); // store the previous sn in the right varial and so frees the

	// consts --------------

	mpfr_t sn_snx;
	mpfr_init2(sn_snx, prec);
	mpfr_snx(sn_snx, n - 1, prec, round);

	mpfr_t u;
	mpfr_init2(u, prec);
	mpfr_sqr(u, sn_snx, round);
	mpfr_add_ui(u, u, 1, round);
	mpfr_mul(u, u, sn_snx, round);
	mpfr_mul_ui(u, u, 8, round);
	mpfr_qtrt(u, u, round);

	mpfr_t t;
	mpfr_init2(t, prec);
	mpfr_add_ui(t, sn_snx, 1, round);

	// mpfr_printf("snx_p: %.60Rf\nu: %.60Rf\n", snx_p, u);

	//--------------

	mpfr_ui_sub(sn, 1, sn_snx, round);
	mpfr_pow_ui(sn, sn, 4, round);

	mpfr_t mul, tmp;
	mpfr_inits2(prec, mul, tmp, (mpfr_ptr)0);

	mpfr_add(mul, t, u, round);
	mpfr_sqr(mul, mul, round);
	mpfr_div(sn, sn, mul, round);

	mpfr_sqr(tmp, u, round);
	mpfr_sqr(mul, t, round);
	mpfr_add(mul, mul, tmp, round);

	mpfr_div(sn, sn, mul, round);

	mpfr_clears(mul, tmp, (mpfr_ptr)0);

	//--------------
	mpfr_clear(snx);
	mpfr_clear(u);
	mpfr_clear(t);

	mpfr_set(rop, sn, round);
}

void mpfr_snx(mpfr_t rop, int n, mpfr_prec_t prec, mpfr_rnd_t round)
{
	assert(n <= ITER);
	assert(n >= -20);

	mpfr_swap(snx, snx_p);

	printf("(snx) n: %i\n", n);
	mpfr_sn(snx, n, prec, round);
	mpfr_pow_ui(snx, snx, 4, round);
	mpfr_ui_sub(snx, 1, snx, round);
	mpfr_qtrt(snx, snx, round);
	mpfr_set(rop, snx, round);
}

void mpfr_an(mpfr_t rop, int n, mpfr_prec_t prec, mpfr_rnd_t round)
{
	assert(n <= ITER);
	printf("(an) n: %i\n", n);

	if (n <= 0)
	{
		mpfr_set_q(rop, a0, round);
		return;
	}

	mpfr_swap(an, an_p);

	mpfr_t sn;
	mpfr_init2(sn, prec);
	mpfr_sn(sn, n, prec, round);

	mpfr_t t, m1, m2;
	mpfr_inits2(prec, t, m1, m2, (mpfr_ptr)0);

	mpfr_snx(t, n - 1, prec, round);
	mpfr_add_ui(t, t, 1, round);
	mpfr_sub_ui(rop, t, 1, round);

	mpfr_add_ui(m1, sn, 1, round);
	mpfr_div(m1, m1, t, round);
	mpfr_pow_ui(m1, m1, 4, round);

	mpfr_pow_si(m2, t, -4, round);

	// mpfr_printf("an-1: %.60Rf\nt : %.60Rf\nm1 : %.60Rf\nm2 : %.60Rf\n", an1, t, m1, m2);

	mpfr_t tmp;
	mpfr_init2(tmp, prec);

	mpfr_mul_si(an, m1, -4, round);
	mpfr_mul_si(tmp, m2, -12, round);
	mpfr_add(an, tmp, an, round);
	mpfr_add_ui(an, an, 1, round);
	////mpfr_printf("PLUS2: %.60Rg\n", an_c[n]);

	mpfr_ui_pow_ui(tmp, 4, (2 * n) - 1, round);
	mpfr_div_ui(tmp, tmp, 3, round);
	// mpfr_printf("PLUS1: %.60Rg\n", tmp);

	mpfr_mul(an, an, tmp, round);
	mpfr_neg(an, an, round);
	// mpfr_printf("PLUS: %.60Rf\n", an_c[n]);

	mpfr_mul_ui(tmp, m1, 16, round);
	mpfr_mul(tmp, tmp, an_p, round);
	// mpfr_printf("start: %.60Rf\n", start);

	mpfr_sub(an, tmp, an, round);
	// mpfr_printf("an: %.60Rf\n", an_c[n]);

	mpfr_clear(sn);
	mpfr_clear(tmp);
	mpfr_clears(t, m1, m2, (mpfr_ptr)0);
	mpfr_set(rop, an, round);
}
#include <stdlib.h>
#include <stdio.h>
#include "c_mpq.h"

#include <mpir.h>

#define ITER 5

//initialisation functions
//--------------------------------------------------------------------------------------------

int mpq_init_set_str(mpq_t rop, char *str, int base)
{
	mpq_init(rop);
	return mpq_set_str(rop, str, base);
}

void mpq_init_set(mpq_t rop, mpq_t op)
{
	mpq_init(rop);
	mpq_set(rop, op);
}

//I/O functions
//--------------------------------------------------------------------------------------------

size_t mpq_dec_out_str (FILE *stream, int base, size_t n_digits, mpq_t op)
{
	mpf_t out;
	mpf_init2(out, n_digits);

  mpf_set_q(out, op);

	mpf_out_str(stream, base, 0, out);

	mpf_clear(out);
}

//aritmetics functions
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

void mpq_2nth_root(mpq_t rop, mpq_t op, int prec, int n)
{
	mpf_t q;
	mpf_init2(q, prec);
	mpf_set_q(q, op);

	for (int i = 0; i < n; ++i) mpf_sqrt(q, q);

	mpq_set_f(rop, q);

	mpf_clear(q);
}

void mpq_pow_ui(mpq_t rop, mpq_t op1, unsigned int op2)
{
	mpf_t tmp;
	mpf_init(tmp);
	mpf_set_q(tmp, op1);

	mpf_pow_ui(tmp, tmp, op2);

	mpq_set_z(rop, tmp);

	mpf_clear(tmp);
}

void mpq_sqrt(mpq_t rop, mpq_t op, int prec)
{
	mpq_2nth_root(rop, op, prec, 1);
}

void mpq_qtrt(mpq_t rop, mpq_t op, int prec)
{
  mpq_2nth_root(rop, op, prec, 2);
}

void mpq_sub_ui(mpq_t rop, mpq_t op1, unsigned int op2)
{
	mpq_t m_op2;
	mpq_init(m_op2);

	mpq_set_ui(m_op2, op2, 1);

	mpq_sub(rop, op1, m_op2);

	mpq_clear(m_op2);
}

void mpq_ui_sub(mpq_t rop, unsigned int op1, mpq_t op2)
{
	mpq_t m_op1;
	mpq_init(m_op1);

	mpq_set_ui(m_op1, op1, 1);

	mpq_sub(rop, m_op1, op2);

	mpq_clear(m_op1);
}

void mpq_add_ui        (mpq_t rop, mpq_t op1, unsigned int op2)
{
	mpq_t m_op2;
	mpq_init(m_op2);

	mpq_set_ui(m_op2, op2, 1);

	mpq_add(rop, m_op2, op1);

	mpq_clear(m_op2);
}
void mpq_ui_add        (mpq_t rop, unsigned int op1, mpq_t op2)
{
	mpq_t m_op1;
	mpq_init(m_op1);

	mpq_set_ui(m_op1, op1, 1);

	mpq_add(rop, m_op1, op2);

	mpq_clear(m_op1);
}

#define CACHE_SIZE ITER + 1

void mpq_sn(mpq_t rop, int n, int prec)
{
	if (n == 1)
	{
		mpq_set_ui(rop, 2, 1);
		mpq_sqrt(rop, rop, prec);
		mpq_sub_ui(rop, rop, 1);
		return;
	}
	mpq_t u, t, sn1x;
	mpq_init(sn1x);
	mpq_snx_wrapper(sn1x, n -1, prec);

	// u ------------------------------------------
	mpq_init_set(u, sn1x);
	mpq_add_ui(u, u, 1);

	// t ------------------------------------------
	mpq_init_set(t, sn1x);
	mpq_pow_ui(t, t, 2);
	mpq_ui_add(t, 1, t);
	mpq_mul(t, t, sn1x);
	mpq_mul(t, t, 8);
	mpq_qtrt(t, t, prec);

	mpq_ui_sub(rop, 1, sn1x);
	mpq_pow_ui(rop, rop, 4);

	mpq_t tmp, tmp2;
	mpq_init_set(tmp, t);
	mpq_init_set(tmp2, t);

	mpq_add(tmp, tmp, u);
	mpq_pow_ui(tmp, tmp, 2);

	mpq_pow_ui(tmp2, tmp2, 2);
	mpq_add


	mpq_div(rop, rop, tmp);

	mpq_clear(tmp);

	mpq_clear(sn1x);
	mpq_clear(t);
	mpq_clear(u);
}

void mpq_sn_wrapper(mpq_t rop, int n, int prec)
{

}

void mpq_snx(mpq_t rop, int n, int prec)
{
	mpq_sn(rop, n, prec);
	mpq_pow_ui(rop, rop, 4);
	mpq_ui_sub(rop, 1, rop);
	mpq_qtrt(rop, rop, prec);
}

void mpq_snx_wrapper(mpq_t rop, int n, int prec)
{
	mpq_t cache[CACHE_SIZE];
	mpq_set(cache[ITER], NULL);

	mpq_inits(cache);

	if (mpq_cmp_ui(cache[n], 0, 1))
	{
		mpq_set(rop, cache[n]);
		return;
	}

	mpq_snx(cache[n], n, prec);

	mpq_set(rop, cache[n]);

	mpq_clears(cache);
}
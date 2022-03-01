#include <stdlib.h>
#include <stdio.h>
#include "c_mpq.h"

#include <mpir.h>

//initialisation functions
//--------------------------------------------------------------------------------------------

int mpq_init_set_str(mpq_t rop, char *str, int base)
{
	mpq_init(rop);
	return mpq_set_str(rop, str, base);
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

void mpq_snx(mpq_t rop, int n)
{
	mpq_pow_ui(rop, sn(n), 2);
}
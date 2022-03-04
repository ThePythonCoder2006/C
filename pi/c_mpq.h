#ifndef C_MPQ_H
#define C_MPQ_H

#include <mpir.h>

int  mpq_init_set_str(mpq_t rop, char *str, int base);
void mpq_init_set    (mpq_t rop, mpq_t op);

int  mpq_get_num_to_mpf(mpf_t rop, mpq_t op);
int  mpq_get_den_to_mpf(mpf_t rop, mpq_t op);
int  mpq_to_mpf        (mpf_t rop, mpq_t op);
void mpq_2nth_root     (mpq_t rop, mpq_t op, int prec, int n);
void mpq_sqrt          (mpq_t rop, mpq_t op, int prec);
void mpq_qtrt          (mpq_t rop, mpq_t op, int prec);
void mpq_pow_ui        (mpq_t rop, mpq_t op1, unsigned int op2);
void mpq_sub_ui        (mpq_t rop, mpq_t op1, unsigned int op2);
void mpq_ui_sub        (mpq_t rop, unsigned int op1, mpq_t op2);
void mpq_add_ui        (mpq_t rop, mpq_t op1, unsigned int op2);
void mpq_ui_add        (mpq_t rop, unsigned int op1, mpq_t op2);

void mpq_snx           (mpq_t rop, int n, int prec);
void mpq_snx_wrapper   (mpq_t rop, int n, int prec);
void mpq_sn            (mpq_t rop, int n, int prec);
void mpq_sn_wrapper    (mpq_t rop, int n, int prec);
size_t mpq_dec_out_str (FILE *stream, int base, size_t n_digits, mpq_t op);

#endif //C_MPQ_H
#include <stdlib.h>
#include <stdio.h>

#include <mpir.h>

int  mpq_init_set_str(mpq_t rop, char *str, int base);

int  mpq_get_num_to_mpf(mpf_t rop, mpq_t op);
int  mpq_get_den_to_mpf(mpf_t rop, mpq_t op);
int  mpq_to_mpf        (mpf_t rop, mpq_t op);
void mpq_sqrt          (mpq_t rop, mpq_t op);
void mpq_qtrt          (mpq_t rop, mpq_t op);
#include <stdlib.h>
#include <stdio.h>

#include <mpir.h>

int mpq_get_num_to_mpf(mpf_t rop, mpq_t op);
int mpq_get_den_to_mpf(mpf_t rop, mpq_t op);
int mpq_to_mpf(mpf_t rop, mpq_t op);
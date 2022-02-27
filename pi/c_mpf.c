#include <stdlib.h>
#include <stdio.h>
#include "c_mpf.h"

#include <mpir.h>

void mpf_qtrt(mpf_t rop, mpf_t op)
{
	mpf_sqrt(rop, op);
	mpf_sqrt(rop, rop);
}
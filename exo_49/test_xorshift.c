#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct xorshift_state
{
	__m256i a;
} xorshift_state;

void xorshift64(xorshift_state *s, __m256i *out);

int main(int argc, char **argv)
{
	xorshift_state *state = calloc(1, sizeof(*state));

	__m256i val = _mm256_set1_epi64x(1);

	xorshift64(state, &val);

	uint64_t *res = (uint64_t *)&val;

	for (uint8_t i = 0; i < 4; ++i)
	{
		printf("%" PRIu64 "\n", res[i]);
	}

	return EXIT_SUCCESS;
}

void xorshift64(xorshift_state *s, __m256i *out)
{
	_mm256_epi64 return;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <inttypes.h>
#include <stdint.h>
#include <immintrin.h>
#include <assert.h>

#ifdef _WIN32
#include <windows.h>
#endif

typedef struct
{
	__m256i a;
} xorshift32_state;

typedef struct
{
	__m256i a[2];
} xorshift64_state;

uint8_t state32_init = 0;
xorshift32_state state32;
uint8_t state64_init = 0;
xorshift64_state state64;

void xorshiftstar32_AVX(__m256i *res, xorshift32_state *st)
{
	__m256i x = st->a;
	x = _mm256_xor_si256(x, _mm256_srli_epi32(x, 12)); // x ^= x >> 12;
	x = _mm256_xor_si256(x, _mm256_slli_epi32(x, 25)); // x ^= x << 25;
	x = _mm256_xor_si256(x, _mm256_srli_epi32(x, 27)); // x ^= x >> 27;
	st->a = x;
	*res = _mm256_mul_epu32(x, _mm256_set1_epi32(0x2545F491U)); // Magic constant for xorshift*
}

void xorshiftstar32_AVX_init(xorshift32_state *st)
{
	st->a = _mm256_set_epi32(rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand());
	state32_init = 1;
}

void xorshiftstar64_AVX(__m256i *res, xorshift64_state *st)
{
	__m256i s1 = st->a[0];
	*res = st->a[1] + s1;
	st->a[0] = st->a[1];
	s1 = _mm256_xor_si256(s1, _mm256_slli_epi32(s1, 23));			 // s1 ^= s1 << 23;
	s1 = _mm256_xor_si256(s1, _mm256_srli_epi32(s1, 18));			 // s1 ^= s1 >> 18;
	s1 = _mm256_xor_si256(s1, st->a[1]);											 // s1 ^= s0;
	s1 = _mm256_xor_si256(s1, _mm256_srli_epi32(st->a[1], 5)); // s1 ^= s0 >> 5;
	st->a[1] = s1;
}

void xorshiftstar64_AVX_init(xorshift64_state *st)
{
	if (state32_init == 0)
		xorshiftstar32_AVX_init(&state32);

	xorshiftstar32_AVX(&(st->a[0]), &state32);
	xorshiftstar32_AVX(&(st->a[1]), &state32);

	state64_init = 1;
}

int main(int argc, char **argv)
{
	// FILE *f = fopen("rand.txt", "w");

	srand(time(NULL));

	xorshiftstar32_AVX_init(&state32);
	xorshiftstar64_AVX_init(&state64);

	__m256i random;

	xorshiftstar64_AVX(&random, &state64);
	printf("[%10u, %10u, %10u, %10u, %10u, %10u, %10u, %10u]\n",
				 ((uint32_t *)&random)[0],
				 ((uint32_t *)&random)[1],
				 ((uint32_t *)&random)[2],
				 ((uint32_t *)&random)[3],
				 ((uint32_t *)&random)[4],
				 ((uint32_t *)&random)[5],
				 ((uint32_t *)&random)[6],
				 ((uint32_t *)&random)[7]);

	printf("what number do you wish to search for ? :\n");
	uint32_t target;
	scanf("%u", &target);
	__m256i targetv = _mm256_set1_epi32(target);

#ifdef _WIN32
	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;
	double interval;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
#endif

	for (uint64_t i = 0; i < UINT32_MAX; i += 8)
	{
		xorshiftstar64_AVX(&random, &state64);
		if (0 && _mm256_testz_si256(_mm256_xor_si256(_mm256_cmpeq_epi32(random, targetv), _mm256_set1_epi32(1)), _mm256_set1_epi32(-1)) != 0)
		{
			printf("%u : [%10u, %10u, %10u, %10u, %10u, %10u, %10u, %10u]\n", i,
						 ((uint32_t *)&random)[0],
						 ((uint32_t *)&random)[1],
						 ((uint32_t *)&random)[2],
						 ((uint32_t *)&random)[3],
						 ((uint32_t *)&random)[4],
						 ((uint32_t *)&random)[5],
						 ((uint32_t *)&random)[6],
						 ((uint32_t *)&random)[7]);
			break;
		}

		if (0 && (i & ((1 << 23) - 1)) == 0)
			printf("%u done\n", i);
	}

#ifdef _WIN32
	QueryPerformanceCounter(&end);
	interval = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1000000;

	printf("%f microseconds\n", interval);

#endif

	return 0;
}
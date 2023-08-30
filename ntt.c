#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#define LEN 8

void ntt_naive(uint32_t *X, size_t n, uint32_t N, uint32_t w);
void intt_naive(uint32_t *X, size_t n, size_t n_inv, uint32_t N, uint32_t w_inv);
void ntt_recursive(uint32_t *X, size_t n, uint32_t N, uint32_t w);
void intt_recursive(uint32_t *X, size_t n, size_t n_inv, uint32_t N, uint32_t w_inv);

int main(int argc, char **argv)
{
  (void)argc, (void)argv;

  uint32_t X[LEN] = {6, 0, 10, 7, 2};
  uint32_t X_naive[LEN] = {6, 0, 10, 7, 2};
  uint32_t X_recursive[LEN] = {6, 0, 10, 7, 2};

  const uint32_t M = 11;
  const uint32_t k = 2;
  const uint32_t N = LEN * k + 1;
  assert(N >= M && "N must be bigger of equal to M");

  const uint32_t g = 3;
  // printf("g^N %% N = %u^%u %% %u = %u\n", g, N, N, (uint32_t)pow(g, N) % N);
  // assert((uint32_t)pow(g, N) % N == 1 && "g must be an N-th primitive root of unity modulo N (a generator)");

  const uint32_t w = (uint32_t)pow(g, k) % N;
  assert((uint32_t)pow(w, LEN) % N == 1 && "something went wrong with the n-th primitive root of unity modulo N");

  // printf("w^n = %u\n", (uint32_t)pow(w, LEN) % N);

  ntt_naive(X_naive, LEN, N, w);

  ntt_recursive(X_recursive, LEN, N, w);

  printf("idx|inp \tniv \trec\n");
  for (uint8_t i = 0; i < LEN; ++i)
    printf("%2u | %2u \t %2u \t %2u\n", i, X[i], X_naive[i], X_recursive[i]);
  putchar('\n');

  return EXIT_SUCCESS;
}

void ntt_naive(uint32_t *X, size_t n, uint32_t N, uint32_t w)
{
  assert((uint32_t)pow(w, n) % N == 1 && "w must be a root of unity mod N");

  uint32_t *Y = calloc(n, sizeof(Y[0]));

  for (uint32_t k = 0; k < n; ++k)
  {
    Y[k] = 0;
    for (uint32_t i = 0; i < n; ++i)
      Y[k] = (Y[k] + (X[i] * (uint32_t)pow(w, i * k))) % N;
  }

  memcpy(X, Y, n * sizeof(X[0]));

  free(Y);

  return;
}

void intt_naive(uint32_t *X, size_t n, size_t n_inv, uint32_t N, uint32_t w_inv)
{
  assert((uint32_t)pow(w_inv, n) % N == 1 && "w must be a root of unity mod N");

  for (uint32_t k = 0; k < n; ++k)
  {
    uint32_t acc = 0;
    for (uint32_t i = 0; i < n; ++i)
      acc = (acc + (X[i] * (uint32_t)pow(w_inv, i * k))) % N;
    acc = (acc * n_inv) % N;
  }

  return;
}

// n must be a power of two
void ntt_recursive(uint32_t *X, size_t n, uint32_t N, uint32_t wn)
{
  assert((uint32_t)pow(wn, n) % N == 1 && "wn must be a root of unity mod N");

  // base case
  if (n == 1)
    return;

  // split the polinomial into odd and even coefficients
  uint32_t *X_e = calloc(n / 2, sizeof(uint32_t)),
           *X_o = calloc(n / 2, sizeof(uint32_t));
  for (uint32_t i = 0; i < n / 2; ++i)
  {
    X_e[i] = X[2 * i];
    X_o[i] = X[2 * i + 1];
  }

  // compute recursive ntt
  ntt_recursive(X_e, n / 2, N, wn * wn % N);
  ntt_recursive(X_o, n / 2, N, wn * wn % N);

  // compute the output with butterfly
  uint32_t w = 1;
  for (uint32_t i = 0; 2 * i < n; ++i)
  {
    X[i] = (X_e[i] + w * X_o[i]) % N;
    X[i + n / 2] = (X_e[i] - w * X_o[i]) % N;
    w = (w * wn) % N;
  }

  free(X_e);
  free(X_o);

  return;
}

#if 0
void intt_recursive(uint32_t* X, uint32_t* Y, size_t n, size_t n_inv, uint32_t N, uint32_t w_inv)
{
  return;
}
#endif
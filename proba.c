#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>

#define MAX_ROLL 1000

#define NTH_BIT(B, N) ((B) & (1 << ((N)-1)))

#define A NTH_BIT(abaNbaUb, 1)
#define B NTH_BIT(abaNbaUb, 2)
#define ANB NTH_BIT(abaNbaUb, 3)
#define AUB NTH_BIT(abaNbaUb, 4)

#define D1 (vals & (0b00001111))
#define D2 ((vals & (0b11110000)) >> 4)

int main(void)
{
  srand(time(NULL));
  {
    uint8_t abaNbaUb = 1;
    uint8_t vals = 0;
    vals ^= (rand() % 6) + 1;
    vals ^= ((rand() % 6) + 1) << 4;
    uint8_t val = D1 + D2;

    abaNbaUb ^= (val % 2);

    abaNbaUb ^= (val >= 6) << 1;

    abaNbaUb ^= (A && B) << 2;

    abaNbaUb ^= (A || B) << 3;

    printf("D n1 : %i, D n2 : %i\n", D1, D2);
    printf("La somme des D est de %i\n", val);
    A ? printf("A realise (%i = %i * 2)\n", val, (int)val / 2) : printf("A pas realise (%i = %i * 2 + 1)\n", val, (int)val / 2);
    B ? printf("B realise (%i >= 6)\n", val) : printf("B pas realise (%i < 6)\n", val);
    ANB ? printf("aNb realise\n") : printf("aNb pas realise\n");
    AUB ? printf("aUb realise\n") : printf("aUb pas realise\n");
  }
  return 0;
}
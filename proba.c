#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>

#define MAX_ROLL 1000

#define NTH_BIT(B, N) ((B) & (1 << ((N)-1)))

#define A NTH_BIT(abaNbaUbval, 1)
#define B NTH_BIT(abaNbaUbval, 2)
#define ANB NTH_BIT(abaNbaUbval, 3)
#define AUB NTH_BIT(abaNbaUbval, 4)

#define D1 (vals & (0b00001111))
#define D2 ((vals & (0b11110000)) >> 4)
#define VAL ((abaNbaUbval & 0b11110000) >> 4)

int main(void)
{
  srand(time(NULL));
  {
    uint8_t abaNbaUbval = 1;
    uint8_t vals = 0;
    vals |= (rand() % 6) + 1;
    vals |= ((rand() % 6) + 1) << 4;
    abaNbaUbval |= ((D1 + D2) << 4);

    abaNbaUbval |= (VAL % 2), abaNbaUbval ^= 1;

    abaNbaUbval |= (VAL >= 6) << 1;

    abaNbaUbval |= (A && B) << 2;

    abaNbaUbval |= (A || B) << 3;

    printf("D n1 : %i, D n2 : %i\n", D1, D2);
    printf("La somme des D est de %i\n", VAL);
    A ? printf("A realise (%i = %i * 2)\n", VAL, (int)VAL / 2) : printf("A pas realise (%i = %i * 2 + 1)\n", VAL, (int)VAL / 2);
    B ? printf("B realise (%i >= 6)\n", VAL) : printf("B pas realise (%i < 6)\n", VAL);
    ANB ? printf("aNb realise (6 < %i = %i * 2 ", VAL, (int)VAL / 2, VAL) : (printf("aNb pas realise ("), (A ? printf("%i = %i * 2 mais %i < 6", VAL, (int)VAL / 2, VAL) : printf("%i > 6 mais %i = %i * 2 + 1", VAL, VAL, (int)VAL / 2))), printf(")\n");
    AUB ? (printf("aUb realise ("), (A ? (printf("%i = %i * 2 ", VAL, (int)VAL / 2), (B ? printf("et %i >= 6", VAL) : printf(""))) : printf("%i > 6", VAL))) : printf("aUb pas realise (%i = %i * 2 + 1 et %i < 6"), printf(")\n");
  }
  return 0;
}
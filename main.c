#include <stdio.h>

void intswap(int **a, int **b)
{
    int *tmp = *a;
    *a = *b;
    *b = *tmp;
}

int main(void)
{
    return 0;
}
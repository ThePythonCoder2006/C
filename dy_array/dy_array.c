#include <stdio.h>
#include <stdlib.h>
#include "dy_array.h"

void int_arr_init(int_Arr *arr, int nEle)
{
    arr->p = malloc(sizeof(int) * nEle + sizeof(arr->p));
}

void int_arr_cls(int_Arr *arr)
{
    free(arr->p);
}
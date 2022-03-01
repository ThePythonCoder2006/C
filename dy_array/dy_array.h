#ifndef DY_ARRAY_H
#define DY_ARRAY_H

typedef struct int_dy_array
{
    int *p;
} int_Arr;

void int_arr_init(int_Arr *arr, int nEle);
void int_arr_cls(int_Arr *arr);

#endif //DY_ARRAY_H
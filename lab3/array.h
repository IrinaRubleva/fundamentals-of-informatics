#ifndef ARRAY_H
#define ARRAY_H

typedef enum Err
{
    ERR_OK = 0,
    ERR_MEM = -1,
} Err;

void array_print(int *arr, int len);
// константный указатель само значение указателя внутри функции можем спокойно менять,
// но через этот указатель мы не можем менять те значения, которые располагаются по тем адресам куда он указывает
Err array_append(int *arr, int *len, int **array);
Err array_insert(int *arr, int *len, int **array);
Err array_delete(int *arr, int *len, int *position);
Err array_indiv(int *arr, int *len);

#endif
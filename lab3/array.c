#include <stdio.h>
#include <stdlib.h>

#include "array.h"

void array_print(int *arr, int len)
{
    if (!len)
    {
        printf("Ops... array is empty\n");
        return;
    }
    for (int i = 0; i < len; ++i)
    {
        printf("array[%d] = %d\n", i, arr[i]);
    }
    return;
}

Err array_append(int *arr, int *len, int **array)
{
    int size = *len;
    int *new_arr = (int *)realloc(arr, (size + 1) * sizeof(int));
    if (new_arr == NULL)
    {
        return ERR_MEM;
    }
    *array = new_arr;
    int val;
    for (int i = 0; i < size; ++i)
    {
        scanf("%d", &val);
        *(new_arr + i) = val;
    }
    *len = size;
    return ERR_OK;
}

Err array_insert(int *arr, int *len, int **array)
{
    int size = *len + 1;
    int *new_arr = (int *)realloc(arr, size * sizeof(int));
    if (new_arr == NULL)
    {
        return ERR_MEM;
    }
    *array = new_arr;
    *len = size;
    int value;
    int position;
    printf("Enter position of element: ");
    scanf("%d", &position);
    printf("Enter value of element: ");
    scanf("%d", &value);
    if (*len == 1)
    {
        printf("Are you sure that you initialized an array?\n");
        return ERR_MEM;
    }
    if (position < 0)
    {
        return ERR_MEM;
    }
    else
    {
        printf("OK1\n");
        if (position > *len)
        {
            position = *len - 1;
        }
        printf("OK2\n");
        for (int i = *len - 2; i >= position; --i)
        {
            *(new_arr + i + 1) = *(new_arr + i);
            printf("OK3\n");
        }
        printf("OK4\n");
        *(new_arr + position) = value;
        printf("OK5\n");
        return ERR_OK;
    }
}

Err array_delete(int *arr, int *len, int *position)
{
    if (*position < 0 || *position >= *len)
    {
        return ERR_MEM;
    }
    else
    {
        for (int i = *position; i < *len - 1; ++i)
        {
            *(arr + i) = *(arr + i + 1);
        }
        (*len)--;
    }
    return ERR_OK;
}

Err array_indiv(int *arr, int *len)
{
    if (*len == 0)
    {
        printf("Oops...Array is empty\n");
        return ERR_MEM;
    }
    int *arr_2 = (int *)malloc((*len) * sizeof(int)); // больше исходного массива новый не будет
    if (arr_2 == NULL)
    {
        fprintf(stderr, "out of memory!\n");
        exit(1);
    }    int tmp;
    int len_2 = 0;
    int *arr_3 = (int *)malloc((*len) * sizeof(int));
    if (arr_3 == NULL)
    {
        fprintf(stderr, "out of memory!\n");
        exit(1);
    }
    for (int i = 0; i < *len - 1; ++i)
    {
        tmp = 0;
        for (int j = i + 1; j < *len; ++j)
        {
            tmp += arr[j];
            if (arr[i] == tmp)
            {
                *(arr_3 + len_2) = i;
                *(arr_2 + len_2) = *(arr + i);
                (len_2)++;
                break;
            }
        }
    }
    for (int i = len_2 - 1; i >= 0; --i)
    {
        array_delete(arr, len, (arr_3 + i));
    }
    array_print(arr_2, len_2);
    free(arr_2);
    free(arr_3);
    return ERR_OK;
}
#include <stdio.h>
#include <stdlib.h>
#include "array.h"

int main()
{
    int len = 2;
    char option = -1;
    int *arr = (int *)malloc(len * sizeof(int));
    int **array = &arr;
    do
    {
        printf("\n");
        printf("*****MENU*****\n");
        printf("(a) Initializing an array\n");
        printf("(b) Inserting a new element\n");
        printf("(c) Deleting an element\n");
        printf("(d) Find the element\n");
        printf("(e) Print array\n");
        printf("(f) Exit\n");
        printf("\n");

        printf("Enter the letter: ");
        int r = scanf(" %c", &option);
        if (r == EOF)
        {
            free(arr);
            return 0;
        }

        switch (option)
        {
        case 'a':
            printf("Enter the lenght of the array: ");
            scanf("%d", &len);
            array_append(arr, &len, array);
            break;
        case 'b':
            array_insert(arr, &len, array);
            array_print(arr, len);
            break;
        case 'c':
            int position;
            scanf("The position of deleted element: ");
            scanf("%d", &position);
            array_delete(arr, &len, &position);
            array_print(arr, len);
            break;
        case 'd':
            array_indiv(arr, &len);
            break;
        case 'e':
            array_print(arr, len);
            break;
        case 'f':
            printf("Exiting...\n");
            break;
            // default:
            //       printf("Wrong input!\n");
            //       break;
        }
    } while (option != 'f');
    free(arr);
    return 0;
}
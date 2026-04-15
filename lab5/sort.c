#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"



int compare_mark(const void *a, const void *b){
	return strcmp(((struct Avto *)a)->mark, ((struct Avto *)b)->mark);
}
int r_compare_mark(const void *a, const void *b){
	return -strcmp(((struct Avto *)a)->mark, ((struct Avto *)b)->mark);
}
int compare_fio(const void *a, const void *b){
	return strcmp(((struct Avto *)a)->fio, ((struct Avto *)b)->fio);
}
int r_compare_fio(const void *a, const void *b){
	return -strcmp(((struct Avto *)a)->fio, ((struct Avto *)b)->fio);	
}
int compare_mileage(const void *a, const void *b){
	return ((struct Avto *)a)->mileage - ((struct Avto *)b)->mileage;	
}
int r_compare_mileage(const void *a, const void *b){
	return -(((struct Avto *)a)->mileage - ((struct Avto *)b)->mileage);	
}



void odd_even(void *first, size_t n, size_t size, int (* comparator) (const void *, const void *));
void insert_binary(void *first, size_t n, size_t size, int (* comparator) (const void *, const void *));



void sort(struct Avto *cars, int n, char *type_sort, char *field_sort, char* direction_sort){
//	int n = sizeof(cars)/sizeof(cars[0]);
	//printf("%s %s %s", type_sort, field_sort, direction_sort);
	//проверка на корректность ввода данных
	if (!(( (strcmp(type_sort, "qsort") == 0)  ||  (strcmp(type_sort, "odd_even")==0) || (strcmp(type_sort, "insert_binary")==0)) && 
	((strcmp(field_sort, "mark")==0) || (strcmp(field_sort, "fio")==0) || (strcmp(field_sort, "mileage")==0)) && 
	((strcmp(direction_sort, "ASC")==0) || (strcmp(direction_sort, "DESC") == 0)))){
		printf("Incorrect sorting data\n");
		return ;
	}
	
 
	if (strcmp(type_sort, "qsort") == 0){
		if (strcmp(field_sort, "mark") == 0){
			if (strcmp(direction_sort, "ASC") == 0){
				printf("3\n");
				qsort(cars, n, sizeof(struct Avto), compare_mark);	
			}
			else{    //DESC
				qsort(cars, n, sizeof(struct Avto), r_compare_mark);
			}
		}
		else if (strcmp(field_sort, "fio") == 0){
			if (strcmp(direction_sort, "ASC") == 0){
				qsort(cars, n, sizeof(struct Avto), compare_fio);
			}
			else{
				qsort(cars, n, sizeof(struct Avto), r_compare_fio);
			}
		}
		else{  //mileage
			if (strcmp(direction_sort, "ASC") == 0){
				qsort(cars, n, sizeof(struct Avto), compare_mileage);
			}
			else{
				qsort(cars, n, sizeof(struct Avto), r_compare_mileage);
			}			
		}
	}


	else if(strcmp(type_sort, "odd_even") == 0){
		if (strcmp(field_sort, "mark") == 0){
			if (strcmp(direction_sort, "ASC") == 0){
				odd_even(cars, n, sizeof(struct Avto), compare_mark);
			}
			else{    //DESC
				odd_even(cars, n, sizeof(struct Avto), r_compare_mark);
			}
		}
		else if (strcmp(field_sort, "fio") == 0){
			if (strcmp(direction_sort, "ASC") == 0){
				odd_even(cars, n, sizeof(struct Avto), compare_fio);
			}
			else{
				odd_even(cars, n, sizeof(struct Avto), r_compare_fio);
			}
		}
		else{  //mileage
			if (strcmp(direction_sort, "ASC") == 0){
				odd_even(cars, n, sizeof(struct Avto), compare_mileage);
			}
			else{
				odd_even(cars, n, sizeof(struct Avto), r_compare_mileage);
			}			
		}		
	} 	


	else{
		if (strcmp(field_sort, "mark") == 0){
			if (strcmp(direction_sort, "ASC") == 0){
				insert_binary(cars, n, sizeof(struct Avto), compare_mark);		//
			}
			else{    //DESC
				insert_binary(cars, n, sizeof(struct Avto), r_compare_mark);		//
			}
		}
		else if (strcmp(field_sort, "fio") == 0){
			if (strcmp(direction_sort, "ASC") == 0){
				insert_binary(cars, n, sizeof(struct Avto), compare_fio);		//	
			}
			else{
				insert_binary(cars, n, sizeof(struct Avto), r_compare_fio);		//
			}
		}
		else{  //mileage
			if (strcmp(direction_sort, "ASC") == 0){
				insert_binary(cars, n, sizeof(struct Avto), compare_mileage);		//	
			}
			else{
				insert_binary(cars, n, sizeof(struct Avto), r_compare_mileage);		//
			}			
		}		
	}
	return ;
}





void odd_even(void *first, size_t n, size_t size, int (* comparator) (const void *, const void *)){
	char * base = (char *)first; //указатель на первый эдемент массива
	char *left, *right, tmp;
	
	int is_sorted = 1;
	
	while(is_sorted != 0){
	is_sorted = 0;
	//for odd
		for (int x = 1; x < n-1; x+=2){
			left = base + x*size;
			right = base + (x+1)*size;
			if (comparator(left, right) > 0){
				//swap()
				for(int k = 0; k < size; k++){
					tmp = *(left + k);
					*(left + k) = *(right + k);
					*(right + k) = tmp;
				}
				is_sorted = 1;
			}
		}

		//for even
		for (int x = 0; x < n-1; x+=2){
			left = base + x*size;
			right = base + (x+1)*size;
			if (comparator(left, right) > 0){
				//swap()
				for(int k = 0; k < size; k++){
					tmp = *(left + k);
					*(left + k) = *(right + k);
					*(right + k) = tmp;
				}
				is_sorted = 1;
			}
		}
	}
	return ;
}


void insert_binary(void *first, size_t n, size_t size, int (* comparator) (const void *, const void *)){
	char * base = (char *)first; //указатель на первый эдемент массива
	int low, hight, mid;
	char *key = (char *)malloc(size);
	if (key == NULL){
		return ;
	}
	
	for (int i = 1; i < n; i++){
		// копируем текущий элемент в key
		memcpy(key, base + i*size, size);

		//binary search
		low = 0;
		hight = i;
		while(low < hight){
			mid = low + (hight - low)/2;
			if(comparator(key, base + mid*size) < 0){
				hight = mid;
			}
			else{
				low = mid + 1;
			}	
		}
		
		//сдвиг вправо
		for(int j = i; j > low; j--){
			memcpy(base + j*size, base + (j-1)*size, size);
		}
		
		//вставка key
		memcpy(base + low*size, key, size);
	}
	free(key);
	return ;
}

//int main(){
//	struct Avto cars[] = {{"AToyota      ", "Ivanov I.I.", 3123.6}, {"Haval      ", "Dubov N.N.", 4800.9}, {"Honda        ", "Dasha B.B. ", 4567.8}, {"AToyota      ", "Ivanov I.", 1235.7}};
//	int n = sizeof(cars)/sizeof(cars[0]);
//	insert_binary(cars, n, sizeof(struct Avto), compare_fio);
//	for(int i = 0; i < n; i++){
//		printf("%s\t%s\t%.2lf\n", cars[i].mark, cars[i].fio, cars[i]. mileage);
//	}
//	return 0;
//}

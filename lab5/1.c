#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include "sort.h"


char *s_gets(char *str, int n);


int main(int argc, char **argv){
	struct Avto *cars = NULL;
	int option_val = 0;
	int n = 0;  //количество структур
	char *file_path = NULL; //путь к файлу
	
	while((option_val = getopt(argc, argv, "hif:b:oa:c:s:p:d:")) != -1){	
		switch(option_val){
			case 'h':
				printf("-h for help");
				printf("Input an array:\n");
				printf("\t-i from stdin\n");
				printf("\t-f [filename] from text file\n");
				printf("\t-b [filename]from binary file\n");
				printf("Output an array:\n");
				printf("\t-o to stdout\n");
				printf("\t-a [filename] to text file\n");
				printf("\t-c [filename] to binary file\n");
				printf("Sort:\n");
				printf("\t-s");
				printf("\ttype of sort: qsort(1)/odd_even(2)/insert_binary(3) to call up sort put the number\n");
				printf("\t-sortable field: mark(1)/fio(2)/mileage(3), put the number\n");
				printf("\t-direction of sorting: increase(1)/decrease(2), put the num\n");
				break;
				
			case 'i':
				printf("Enter the number of cars you want to enter: ");
				scanf("%d", &n);
				getchar();

				struct Avto *tmp = (struct Avto *)realloc(cars, (n+1)*sizeof(struct Avto));
				if (tmp == NULL){
					printf("Memory allocation error");
					free(cars);
					return 1;
				}
				cars = tmp;
				
				for (int i = 0; i < n; ++i){
					printf("Еnter mark of car: ");
					s_gets(cars[i].mark, sizeof(cars[i].mark));
					
					printf("Еnter last name, firs name and patronymic: ");
					s_gets(cars[i].fio, sizeof(cars[i].fio));
					
					printf("Enter mileage of car: ");
					scanf("%lf", &cars[i].mileage);
					getchar();
				}
				break;
				
			case 'f':
				FILE *file_txt = fopen(optarg, "r");  // "r" - открыть файл для чтения
				if (file_txt == NULL){
					printf("File is empty");
					free(cars);
					return 1;
				}
				n = 0;
				//while(!feof(file_txt)){
				while(fscanf(file_txt, "%15s", cars[n].mark)==1){
					struct Avto *tmp = (struct Avto *)realloc(cars, (n+1)*sizeof(struct Avto));
					if (tmp == NULL){
						fclose(file_txt);
						free(cars);
						return 1;
					}
					cars = tmp;
					
					//fscanf(file_txt, "%15s", cars[n].mark);
					char word[100];
					word[0] = '\0';
					cars[n].fio[0] = '\0';
					while ((fscanf(file_txt, "%99s", word) == 1)  &&  ((strspn(word, "0123456789") != strlen(word)))){ //успешно считали один элемент
						strcat(cars[n].fio, word);
						strcat(cars[n].fio, " ");
					}
					printf("%s", cars[n].fio);
					char *endptr;
					cars[n].mileage = strtol(word, &endptr, 10);
					n++;
				}
				fclose(file_txt);
				break;
				
			case 'b':
				FILE *file_bin = fopen(optarg, "rb");  // "r" - открыть файл для чтения

				if (file_bin == NULL){
					printf("File is empty\n");
					free(cars);
					return 1;
				}
				
				struct Avto *tmp1 = (struct Avto*)realloc(cars, (n+1)*sizeof(struct Avto));
				if (tmp1 == NULL){
					fclose(file_bin);
					free(cars);
					return 1;
				}
				cars = tmp1;
				
				char number[15];
				n = 0;
				double res = 0;
				int fordot = 0;

				
				while(fread(&cars[n].mark, sizeof(char), 15, file_bin) == 15){

					cars[n].fio[0] = '\0';
					char ch;
					while (fread(&ch, sizeof(char), 1 ,file_bin) == 1){
						if(isdigit(ch)){
							fseek(file_bin, -1, SEEK_CUR);
							break;
						}
						strncat(cars[n].fio, &ch, 1);
					}

					memset(number, 0, sizeof(number));
					char ch2;
					while (fread(&ch2, sizeof(char), 1 ,file_bin) == 1){
						if(ch2 == '\n'){
							fseek(file_bin, -1, SEEK_CUR);
							break;
						}
						strncat(number, &ch2, 1);
					}

					res = 0;
					fordot = 0;
					//перевод из строки в double
					for(int i = 0; number[i] != '\0' && number[i] != '\n'; i++){
						if(fordot){
							fordot += 1;
						}
						if (number[i] == '.'){
							fordot += 1;
							continue;
						}
						res = 10*res + number[i] - 48;	
					}
					fordot -= 1;
					while(fordot){
						res /= 10;
						fordot -= 1;
					}
					
					cars[n].mileage = res;
					fseek(file_bin, 1, SEEK_CUR);  //пропуск /n
					n++;
					struct Avto *tmp2 = (struct Avto*)realloc(cars, (n+1)*sizeof(struct Avto));
					if (tmp2 == NULL){
						fclose(file_bin);
						free(cars);
						return 1;
					}
					cars = tmp2;
				}
				fclose(file_bin);
				break;




				
			case 's':
			char *type_sort = NULL;
			char *field_sort = 	NULL;
			char *direction_sort = 	NULL;
			if(atoi(optarg)/100 == 1){
				type_sort = "qsort";
			}
			if(atoi(optarg)/100 == 2){
				type_sort = "odd_even";
			}
			if(atoi(optarg)/100 == 3){
				type_sort = "insert_binary";
			}


			if((atoi(optarg)/10)%10 == 1){
				field_sort = "mark";
			}
			if((atoi(optarg)/10)%10 == 2){
				field_sort = "fio";
			}
			if((atoi(optarg)/10)%10 == 3){
				field_sort = "mileage";
			}


			if(atoi(optarg)%10 == 1){
				direction_sort = "ASC";
			}
			if(atoi(optarg)%10 == 2){
				direction_sort = "DESC";
			}
			
			sort(cars, n, type_sort, field_sort, direction_sort);
			break;


				
			case 'o':
				for (int i = 0; i < n; i++){
				printf("%d\n", i+1);
				printf("\"%s\"\n", cars[i].mark);
				printf("\"%s\"\n", cars[i].fio);
                printf("%lf\n", cars[i].mileage);
				}
				break;
				
			case 'a':
				FILE *file_tout = fopen(optarg, "w");
				printf("%d\n", n);
				if (!file_tout){
					free(cars);
					return 1;
				}

				for(int i = 0; i < n; i++){
					fprintf(file_tout, "%s %s %lf\n", cars[i].mark, cars[i].fio, cars[i].mileage);
				}
				fclose(file_tout); 
				break;
				
			case 'c':
				FILE *file_bout = fopen(optarg, "rw");
				printf("%d\n", n);
				if (!file_bout){
					free(cars);
					return 1;
				}

				for(int i = 0; i < n; i++){
					fprintf(file_bout, "%s %s %lf\n", cars[i].mark, cars[i].fio, cars[i].mileage);
				}
				fclose(file_bout); 
				break;	

			default:
				break;
		}
	}

	if(cars != NULL){
		free(cars);
	}
	return 0;	
}






//пратт 573
char *s_gets(char *str, int n){  // удаление \n для правильной работы fgets()
	char * find;
	char * rev_val = fgets(str, n, stdin);
	if(rev_val){
		find = strchr(str, '\n');
		if (find){
			*find = '\0';
		}
		else{
			while(getchar() != '\n'){
				continue;
			}
		}	
	}
	return rev_val;
}

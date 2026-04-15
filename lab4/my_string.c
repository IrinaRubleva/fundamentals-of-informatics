#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFSIZE 81

int my_strlen(const char *str){
	const char *end = str;
	while (*end != '\0'){
		end ++;
	}
	return (int)(end - str);
}


int my_strcmp(const char *str1, const char *str2){
	while(*str1 != '\0' && *str2 != '\0' && *str1==*str2){
		str1++;
		str2++;
	}
	return *str1-*str2;
}


char *my_strcat(char *res, const char *str){
	while(*res != '\0'){
		res++;
	}
	while(*str != '\0'){
		*res = *str;
		res++;
		str++;
	}
	*res = '\0';
	return res;
}


char *my_strdup(const char *str){
	char *str_copy = (char *)malloc(my_strlen(str) + 1); // +1 для '\0'
	char *point_copy = str_copy; //malloc может поменять место нахождение !!!!!!!!!
	while(*str != '\0'){
		*point_copy = *str;
		str++;
		point_copy++;
	}
	*point_copy = '\0';
 	return str_copy;
}



int chek_del(char symbol, char *delim){
	for (int i = 0; i < my_strlen(delim); ++i){
		if (symbol == delim[i]){
			return 1;
		}
	}
	return 0;
}


char *my_strtok(char *str, char *delim){
	static char *new_str = NULL;
	// если str == NULL, продолжаем работать с последнего сохраненного указателя	
	if (str == NULL){
		str = new_str;
		if (str == NULL){
			return NULL;
		}
	}
	// если первые элементы - это элементы-делители
	while(*str != '\0'){
		if (chek_del(*str, delim)){
			str++;}
		else{
			break;}
	}

	//находим конец выделяемой строки
	char *res = str;
	while(*str != '\0'){
		char *d = delim;
		while(*d != '\0'){
			if(*str == *d){
				*str = '\0';
				new_str = str + 1;
				return res;
			}
			d++;
		}
		str ++;
	}

	new_str = NULL;
	return res;
}




char *my_readline(){
	char buf[81] = {0};
	char *res = NULL;
	int len = 0;
	int n = 0;

	do{
		n = scanf("%80[^\n]", buf);
		if (n < 0){
			if (!res){
				return NULL;
			}
		}
		else if (n > 0){
			int chunk_len = my_strlen(buf);
			int str_len = len + chunk_len;
			res = realloc(res, str_len + 1);
			memcpy(res + len, buf, chunk_len);
			len = str_len;
		}
		else{
			scanf("%*c");
		}
	}while(n > 0);

	if (len > 0){
		res[len] = '\0';
	}
	else{
		res = calloc(1, sizeof(char));
	}
	return res;
}

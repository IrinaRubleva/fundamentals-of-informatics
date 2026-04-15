#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prog.h"



//произвольное количество строк произвольной длины
//строка содержит одно или более строк, разделенных пробелами или табуляцией
//каждая строка представдена списоком. эдементы содержат по два поля, первое - символ, второе - указатель на следующий элемент

int main(){
	char s;
	struct Node *head = NULL;
	while((s = getchar()) != EOF){
		if (s != '\n'){
			append_list();			
		}
		else{
			printf("\"");
			add_list();
			print_list("\"\n");
			printf("\"");
			alpha();
			printf("\"\n");
		}
	}
}

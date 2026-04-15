#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include <readline/readline.h>

#include <time.h>

#define DEL " \t"
#define STR "> "



char** split_str(const char *str, int *word_count); //разделить строку на слова, возвращаю массив из слов
void sort_str(char *word); // сортирую по алфавитному порядку одну строку массива
void delete_anagrams(char **words, int *word_count); //найти и удалить анаграммы
char *join_words(char **words, int word_count); // собрать обратно строку


int main(){
	//printf(STR);
	//char *input = readline(STR);
	//if (input == NULL){
	//	return 1;
	//}


	static const char array_symbol[] = {"qwertyu iopasdfgh jklzxcvb nmQWERTYU IOPASDFG HJKLZX CVBNM"};
	srand(time(NULL));
	int len = 0;
	printf("Enter number of symbol you want to enter: ");
	scanf("%d", &len);
	getchar();

	char *input = (char *)malloc((len+1)*sizeof(char));
	for (int i = 0; i < len; i++){
		input[i] = array_symbol[rand()% (sizeof(array_symbol)-1)]; 
	}
	input[len] = '\0';

	clock_t start, end;
	double my_time = 0;
	int word_count;
	int c = 0; //количество слов, которые надо удалить
	char **words;
	char *res;

	
	while (input != NULL){

		start = clock();

		printf("\"%s\"\n", input);
		words = split_str(input, &word_count);
		res = join_words(words, word_count);
		printf("\"%s\"\n", res);

		end = clock();
		my_time = (double)(end - start)/CLOCKS_PER_SEC;
		printf("Time: %lf\n", my_time);
		
		free(words);
		free(input);
		free(res);
//		input = readline(STR);
	}
	return 0;
}


char** split_str(const char *str, int *word_count){
	char *str_copy = my_strdup(str);
	*word_count = 0;
	char **words = NULL;
	char *word = my_strtok(str_copy, DEL);

	while(word != NULL){
		words = realloc(words, (*word_count + 1)*sizeof(char*));
		words[*word_count] = my_strdup(word);
		(*word_count)++;

		word = my_strtok(NULL, DEL);
	}
	free(str_copy); // т.к. пользовалась strdup()
	return words;
}


void sort_word(char *word){
	int len = my_strlen(word);
	for (int i = 0; i < len - 1; ++i){
		for (int j = i + 1; j < len; ++j){
			if (word[i] > word[j]){
				char tmp = word[i];
				//printf("%c\n", tmp);
				word[i] = word[j];
				word[j] = tmp;
			}
		}
	}
}



void delete_anagrams(char **words, int *word_count){
	char **change_array = (char **)malloc(*word_count * sizeof(char *));

	for (int i = 0; i < *word_count; ++i){
		change_array[i] = my_strdup(words[i]);
		sort_word(*(change_array + i));
	}

	int *index_array = (int *)malloc(*word_count * sizeof(int));
	int c = 0;

	for(int i = 0; i < *word_count; ++i){
		for(int j = 0; j < *word_count; ++j){
			if ((i != j) & (my_strcmp(*(change_array + i),*(change_array + j)) == 0)){
				index_array[c] = i;
				c++;
				break;
			}
		}
 	}

	for (int i = c-1; i >= 0; --i){
		for (int j = index_array[i]; j < *word_count - 1; ++j){
			words[j] = words[j+1];
		}
	}
	(*word_count) -= c;
	free(index_array);
	free(change_array);
}


char *join_words(char **words, int word_count){
	int len = 0;
	for (int i = 0; i < word_count; ++i){
		len += (my_strlen(*(words + i)) + 1);
	}

	char *res = (char*)malloc(len);
	res[0] = '\0';
	for (int i = 0; i < word_count; ++i){
		my_strcat(res, words[i]);
		if (i < word_count - 1){
			my_strcat(res, " ");
		}
	}
	return res;
}

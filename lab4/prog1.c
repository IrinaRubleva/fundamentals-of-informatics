#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>


#define DEL " \t"
#define STR "> "



char** split_str(const char *str, int *word_count); //разделить строку на слова, возвращаю массив из слов
void sort_str(char *word); // сортирую по алфавитному порядку одну строку массива
void delete_anagrams(char **words, int *word_count); //найти и удалить анаграммы
char *join_words(char **words, int word_count); // собрать обратно строку


int main(){
	char *input = readline(STR);
	if (input == NULL){
		return 1;
	}
	int word_count;
	int c = 0; //количество слов, которые надо удалить
	char **words;
	char *res;

	while (input != NULL){
	
		printf("\"%s\"\n", input); // \" - это экранизация двойных ковычек

		words = split_str(input, &word_count);

		delete_anagrams(words, &word_count);

		res = join_words(words, word_count);
		printf("\"%s\"\n", res);

		free(words);
		free(input);
		free(res);
		input = readline(STR);
	}
	return 0;
}


char** split_str(const char *str, int *word_count){
	char *str_copy = strdup(str);
	*word_count = 0;
	char **words = NULL;
	char *word = strtok(str_copy, DEL);
	
	while(word != NULL){
		words = realloc(words, (*word_count + 1)*sizeof(char*));
		words[*word_count] = strdup(word);
		(*word_count)++;
		
		word = strtok(NULL, DEL);
	}
	free(str_copy); // т.к. пользовалась strdup()
	return words;
}



//сортировка обменом
void sort_word(char *word){  
	int len = strlen(word);
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
		change_array[i] = strdup(words[i]);
		sort_word(*(change_array + i));

	int *index_array = (int *)malloc(*word_count * sizeof(int));
	int c = 0;

	for(int i = 0; i < *word_count; ++i){
		for(int j = 0; j < *word_count; ++j){
	//		printf("i=%d j=%d\n", i, j);
			if ((i != j) && (strcmp(*(change_array + i),*(change_array + j)) == 0)){
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
		len += (strlen(*(words + i)) + 1);
	}

	char *res = (char*)malloc(len);
	res[0] = '\0';
	for (int i = 0; i < word_count; ++i){
		strcat(res, words[i]);
		if (i < word_count - 1){
			strcat(res, " ");
		}
	}
	return res;
}

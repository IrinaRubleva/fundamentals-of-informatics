#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//#include "prog.h"


typedef struct ListNode{
	char symbol;
	struct ListNode *next; //ссылка на следующий указатель
} ListNode;



void print_list(ListNode *head){
	int space = 0;
	while(head != NULL){
		if(head->symbol == ' ' || head->symbol == '\t'){
			if(!space){
				printf(" ");
				space = 1;
			}
		}
		else{
			printf("%c", head->symbol);
			space = 0;
		}
		head = head->next;
	}
	//printf("\n");
}


void append_list(ListNode **head, char c){
//	ListNode *node_c = create_list(c);

	ListNode* node_c = (ListNode*)malloc(sizeof(ListNode));
	if (node_c == NULL){
		printf("ERROR");
		exit(1);
	}
	node_c ->symbol = c;
	node_c ->next = NULL;
	
	//если список пустой
	if(*head == NULL){
		*head = node_c;
		return;
	}

	ListNode *last = *head;
	while(last->next != NULL){
		last = last->next;
	}

	last->next = node_c;
}


void free_list(ListNode *head){
	ListNode *tmp;
	while(head != NULL){
		tmp = head;
		head = head->next;
		free(tmp);
	}
}


void alpha(ListNode *head){
//	if (head == NULL){
//		return;
//	}
	ListNode *curr = head;
	while(curr != NULL){
		if(curr->symbol == ' ' || curr->symbol == '\t'){
			curr = curr->next;
			continue;
		}
		
		ListNode *word_end = curr;
		while(word_end != NULL && word_end->symbol != ' ' && word_end->symbol != '\t'){
			word_end = word_end->next;
		}
		ListNode *start = curr;
		while(start != word_end){
			ListNode *min = start;
			ListNode *tmp = start->next;
			while(tmp != word_end){
				if(tmp->symbol < min->symbol){
					min = tmp;
				}
				tmp = tmp->next;
			}
			//меняем символы местами
			if(min != start){
				char tmp_ch = min->symbol;
				min->symbol = start->symbol;
				start->symbol = tmp_ch;
			}
			start = start->next;
		}
		curr = word_end;
	}
}


int main(){
	ListNode *head = NULL;
	char c;
	printf("> ");
	while((c = getchar()) != '\n' && c != EOF){
		append_list(&head, c);
	}
	printf("\"");
	print_list(head);
	printf("\"\n");
	alpha(head);
	printf("\"");
	print_list(head);
	printf("\"\n");

	free_list(head);
	return 0;
}

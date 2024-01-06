#include <stdio.h>
#include <stdlib.h>
#include "program.h"

void push(struct Element** head, int value){
    struct Element* new = NULL;
    new = (struct Element*) malloc(sizeof(struct Element));
    if(new == NULL){
        printf("ERROR: HEAP OVERFLOW\n");
        return;
    }
    new->value = value;
    new->next = *head;
    *head = new;
    return;
}

int pop(struct Element** head){
    if(*head == NULL){
        printf("ERROR: STACK UNDERFLOW (Stack is empty)\n");
        return -1;
    }
    int result = (*head)->value;
    struct Element* old = *head;
    *head = (*head)->next;
    free(old);
    return(result);
}

int top(struct Element** head){
    if(*head == NULL){
        printf("ERROR: STACK IS EMPTY\n");
    }
    int result = (*head)->value;
    return result;
}

void program_init(int position, struct program_state* program){
    struct Element* loop_stack = malloc(sizeof(struct Element));
    program->loop_stack = loop_stack;
    program->position = position;
}
void program_free(struct program_state* program){
    free(program->loop_stack);
    free(program);
}
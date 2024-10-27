#ifndef STACK_H
#define STACK_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node_stack {
    char* value;
    struct Node_stack *next;
} Node_stack;

typedef struct {
    Node_stack *top;
} Stack;

Node_stack* createNodeStack(const char* value);
Stack* createStack();
int isEmpty(const Stack *stack);
void push(Stack *stack, const char* value);
char* pop(Stack *stack);
void print_stack(const Stack *stack);
char* top(const Stack *stack);
void free_stack(Stack* stack);

#endif //STACK_H




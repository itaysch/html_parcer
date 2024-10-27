#include "stack.h"


Node_stack* createNodeStack(const char* value) {
    Node_stack *node = (Node_stack *)malloc(sizeof(Node_stack));
    node->value = (char*)malloc(strlen(value) + 1);  // +1 for the null terminator
    strcpy(node->value, value);
    node->next = NULL;
    return node;
}

Stack* createStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

int isEmpty(const Stack *stack) {
    return stack->top == NULL;
}

void push(Stack *stack, const char* value) {
    Node_stack *node = createNodeStack(value);
    node->next = stack->top;
    stack->top = node;
}

char* pop(Stack *stack) {
    if(isEmpty(stack)) {
        return NULL;
    }
    Node_stack* temp = stack->top;
    char* popped = temp->value;
    stack->top = temp->next;
    free(temp);
    return popped;
}

void print_stack(const Stack *stack) {
    if(isEmpty(stack)) {
        printf("stack is empty\n");
        return;
    }
    printf("Stack: ");
    Node_stack *node = stack->top;
    while(node != NULL) {
        printf("%s ", node->value);
        node = node->next;
    }
    printf("\n");
}

char* top(const Stack *stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    return stack->top->value;
}

void free_stack(Stack* stack) {
    while (!isEmpty(stack)) {
        free(pop(stack));  // Free each node value
    }
    free(stack);  // Free the stack structure itself
}
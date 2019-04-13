#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#ifndef DATA_STRUCTURES_STACK_H
#define DATA_STRUCTURES_STACK_H


typedef struct {
    int size;       // the current size of the stack
    int max_size;   // the maximum size of the stack
    char **_stack;  // the stack array for storing the pointers
} stack_t;

void destroy_stack(stack_t *stack);
stack_t * create_stack(int maxsize);
int push(stack_t *stack, char *str);
char *pop(stack_t *stack);

#endif //DATA_STRUCTURES_STACK_H

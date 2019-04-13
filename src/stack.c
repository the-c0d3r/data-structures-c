#include "stack.h"

/**
 * Creates and return a allocated stack pointer
 * @return: stack_t pointer | NULL
 */
stack_t * create_stack(int maxsize) {
    stack_t *stack = malloc(1 * sizeof(stack_t));
    if (stack) {
        // allocate char pointer array for storing elements
        char **_stack = malloc(maxsize * sizeof(char *));
        if (!_stack) {
            perror("Error allocating memory");
            destroy_stack(stack);
            return NULL;
        }
        stack->max_size = maxsize;
        stack->_stack = _stack;
        stack->size = 0;

        return stack;
    } else {
        perror("Error allocating memory");
        return NULL;
    }
}

/**
 * Destroys the stack by properly freeing the malloced
 * memory block
 * @param stack: the stack pointer to be freed
 */
void destroy_stack(stack_t *stack) {
    for (int i=0; i<stack->size; i++) {
        free(stack->_stack[i]);
    }

    free(stack->_stack);
    free(stack);
}

/**
 * Pushes the char array into the stack
 * @param stack: the stack to push to
 * @param str: the char array value to push
 * @return: 0 on success, 1 on failure
 */
int push(stack_t *stack, char *str) {
    // check for maximum size
    if (stack->size >= stack->max_size) {
        return 1;
    }

    // copy the char array into malloced array
    char *ptr = (char *) malloc(strlen(str) * sizeof(char));
    if (!ptr) {
        perror("Error malloc could not get a free memory block");
        return 1;
    }
    strncpy(ptr, str, strlen(str) + 1);
    stack->_stack[stack->size++] = ptr;
    return 0;
}

/**
 * Pops the stack
 * @param stack: The stack to pop
 * @return: char* of the element or NULL
 * TODO: solve the bug on return
 */
char *pop(stack_t *stack) {
    if (stack->size == 0) {
        printf("Stack size is zero\n");
        return NULL;
    }
    return stack->_stack[--stack->size];

}

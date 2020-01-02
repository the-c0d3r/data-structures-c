#ifndef DATA_STRUCTURES_DOUBLELINKEDLIST_H
#define DATA_STRUCTURES_DOUBLELINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
    int value;
    struct node_t* next;
    struct node_t* prev;
} node_t;

typedef struct {
    struct node_t* head;
    struct node_t* last;
    int size;
} double_linkedlist_t;

// NODE functions
node_t* create_node(int value);

void destroy_node(node_t* node);

// DOUBLE LINKEDLIST functions
double_linkedlist_t* create_double_linkedlist();

int insert(double_linkedlist_t* dlinkedlist, node_t* node);

int delete(double_linkedlist_t* dlinkedlist, node_t* node);

node_t* get(double_linkedlist_t* dlinkedlist, int index);

node_t* pop(double_linkedlist_t* dlinkedlist);

int destroy(double_linkedlist_t* dlinkedlist);

#endif //DATA_STRUCTURES_DOUBLELINKEDLIST_H

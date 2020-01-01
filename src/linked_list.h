#include <stdlib.h>

#ifndef DATA_STRUCTURES_LINKED_LIST_H
#define DATA_STRUCTURES_LINKED_LIST_H


typedef struct node_t {
    int value;
    struct node_t* next;
} node_t;

typedef struct {
    struct node_t* head;
    struct node_t* last;
    int size;
} linkedlist_t;


// NODE Functions
node_t* create_node(int value);

void destroy_node(node_t* node);

// LINKEDLIST Functions
linkedlist_t* create_linkedlist();

int insert(linkedlist_t* linkedlist, node_t* node);

int delete(linkedlist_t* linkedlist, node_t* node);

node_t* get(linkedlist_t* linkedlist, int index);

node_t* pop(linkedlist_t* linkedlist);

int destroy(linkedlist_t* linkedlist);
#endif //DATA_STRUCTURES_LINKED_LIST_H

#include "doublelinkedlist.h"

/**
 * @brief creates a new node
 * @param value: the value to write to
 * @return: ptr to newly created node || null
 */
node_t* create_node(int value) {
    node_t* node = malloc(1 * sizeof(node_t));
    if (node) {
        node->value = value;
        node->next = NULL;
        node->prev = NULL;
        return node;
    } else {
        perror("Error allocating memory\n");
        return NULL;
    }
}

/**
 * @brief destroy the node properly
 * @param node: the node to delete
 */
void destroy_node(node_t* node) {
    free(node);
}

/**
 * @brief function to create new double linkedlist
 * @return: ptr to newly created double linkedlist || null
 */
double_linkedlist_t* create_double_linkedlist() {
    double_linkedlist_t* dlinkedlist = malloc(1 * sizeof(double_linkedlist_t));
    if (!dlinkedlist) {
        perror("Error allocating memory\n");
        return NULL;
    }
    dlinkedlist->size = 0;
    dlinkedlist->head = NULL;
    dlinkedlist->tail = NULL;
    return dlinkedlist;
}

/**
 * @brief function to insert node into the list
 * @param dlinkedlist: double linked list
 * @param node: the node to insert
 * @return: 0 on success | 1 on failure
 */
int insert(double_linkedlist_t* dlinkedlist, node_t* node) {
    if (!dlinkedlist || !node) return 1;

    // empty linkedlist
    if (dlinkedlist->size == 0) {
        dlinkedlist->head = node;
        dlinkedlist->tail = node;
        dlinkedlist->size++;
    } else {
        dlinkedlist->tail->next = node;
        node->prev = dlinkedlist->tail;
        dlinkedlist->tail = node;
        dlinkedlist->size++;
    }

    return 0;
}

/**
 * @brief function to remove the node from dlinkedlist
 * @param dlinkedlist: the double linkedlist
 * @param node: the node to remove
 * @return: 0 on success | 1 on failure
 */
int delete(double_linkedlist_t* dlinkedlist, node_t* node) {
    if (!dlinkedlist || !node || dlinkedlist->size == 0) return 1;

    // case when node is the only node
    if (dlinkedlist->size == 1) {
        destroy_node(node);
        dlinkedlist->head = NULL;
        dlinkedlist->tail = NULL;
        dlinkedlist->size--;
        return 0;
    }

    node_t* pointer = dlinkedlist->head;
    while (pointer) {
        if (pointer == node) break;
        pointer = pointer->next;
    }
    // if node is not found return 1
    if (!pointer) return 1;

    // case when tail node
    if (node == dlinkedlist->tail) {
        dlinkedlist->tail = pointer->prev;
        pointer->prev->next = pointer->next;
    } else if (node == dlinkedlist->head) {
        dlinkedlist->head = pointer->next;
        pointer->next->prev = pointer->prev;
    } else {
        pointer->prev->next = pointer->next;
        pointer->next->prev = pointer->prev;
    }

    destroy_node(pointer);
    dlinkedlist->size--;
    return 0;
}

/**
 * @brief function to properly destroy the dlinkedlist
 * @param dlinkedlist: the dlinkedlist to destroy
 * @return: 0 on success || 1 on failure
 */
int destroy(double_linkedlist_t* dlinkedlist) {
    if (!dlinkedlist) return 1;

    node_t* pointer = dlinkedlist->head;
    node_t* temp = NULL;
    while (pointer) {
        temp = pointer->next;
        destroy_node(pointer);
        pointer = temp;
    }

    free(dlinkedlist);
    return 0;
}

/**
 * @brief function to pop the tail item
 * @param dlinkedlist
 * @return: tail node || NULL
 */
node_t* pop(double_linkedlist_t* dlinkedlist) {
    if (!dlinkedlist || dlinkedlist->size == 0) return NULL;

    node_t* pointer = NULL;
    if (dlinkedlist->size == 1) {
        pointer = dlinkedlist->head;
        dlinkedlist->head = NULL;
        dlinkedlist->tail = NULL;
        dlinkedlist->size--;
        return pointer;
    }

    pointer = dlinkedlist->tail;
    pointer->prev->next = NULL;
    dlinkedlist->tail = pointer->prev;
    dlinkedlist->size--;

    return pointer;
}

/**
 * @brief function to get the node at index
 * @param dlinkedlist: the dlinkedlist to get
 * @param index: the index of the node
 * @return: node_t* || NULL
 */
node_t* get(double_linkedlist_t* dlinkedlist, int index) {
    if (!dlinkedlist || (index < 0 || index > dlinkedlist->size)) return NULL;

    int count = 0;
    node_t* pointer = dlinkedlist->head;
    while (pointer) {
        if (count == index)
            return pointer;
        count++;
        pointer = pointer->next;
    }
    return NULL;
}


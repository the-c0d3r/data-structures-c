#include "linkedlist.h"

/**
 * @brief creates a new node
 * @param value: the value to write to
 * @return: ptr to newly created node || null
 */
node_t* create_node(int value) {
    node_t* node = malloc(1 * sizeof(node_t));
    if (node) {
        node->value = value;
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
 * @brief: function to create new linkedlist
 * @return: ptr to newly created linkedlist || null
 */
linkedlist_t* create_linkedlist() {
    linkedlist_t* linkedlist = malloc(1 * sizeof(linkedlist_t));
    if (!linkedlist) {
        perror("Error allocating memory\n");
        return NULL;
    }
    linkedlist->size = 0;
    linkedlist->head = NULL;
    linkedlist->tail = NULL;
    return linkedlist;
}

/**
 * @brief: function to insert the node into the linkedlist
 * @param linkedlist: linkedlist to insert
 * @param node: the node to insert
 * @return: 0 on success | 1 on failure
 */
int insert(linkedlist_t* linkedlist, node_t* node) {
    if (!linkedlist || !node) return 1;

    // empty linkedlist
    if (linkedlist->size == 0) {
        linkedlist->head = node;
        linkedlist->tail = node;
        linkedlist->size++;
    } else {
        linkedlist->tail->next = node;
        linkedlist->tail = node;
        linkedlist->size++;
    }

    return 0;
}

/**
 * @brief function to remove node from linkedlist
 * @param linkedlist: the linkedlist to delete
 * @param node: the node to delete
 * @return: 0 on success | 1 on failure
 */
int delete(linkedlist_t* linkedlist, node_t* node) {
    if (!linkedlist || !node || linkedlist->size == 0) return 1;

    // case when node is the only node
    if (linkedlist->size == 1) {
        destroy_node(node);
        linkedlist->head = NULL;
        linkedlist->tail = NULL;
        linkedlist->size--;
        return 0;
    }

    node_t* pointer = linkedlist->head;
    node_t* prev = pointer;
    while (pointer) {
        if (pointer == node) break;
        prev = pointer;
        pointer = pointer->next;
    }
    // if node is not found return 1
    if (!pointer) return 1;

    prev->next = pointer->next;
    // case when tail node
    if (node == linkedlist->tail)
        linkedlist->tail = prev;
    if (node == linkedlist->head)
        linkedlist->head = pointer->next;

    destroy_node(pointer);
    linkedlist->size--;
    return 0;
}

/**
 * @brief function to properly destroy the linkedlist
 * @param linkedlist: the linkedlist to destroy
 * @return: 0 on success || 1 on failure
 */
int destroy(linkedlist_t* linkedlist) {
    if (!linkedlist) return 1;

    node_t* pointer = linkedlist->head;
    node_t* temp = NULL;
    while (pointer) {
        temp = pointer->next;
        destroy_node(pointer);
        pointer = temp;
    }

    free(linkedlist);
    return 0;
}

/**
 * @brief function to pop the tail item
 * @param linkedlist
 * @return: tail node || NULL
 */
node_t* pop(linkedlist_t* linkedlist) {
    if (!linkedlist || linkedlist->size == 0) return NULL;

    node_t* pointer = NULL;
    if (linkedlist->size == 1) {
        pointer = linkedlist->head;
        linkedlist->head = NULL;
        linkedlist->tail = NULL;
        linkedlist->size--;
        return pointer;
    }

    pointer = linkedlist->head;
    while (pointer) {
        if (pointer->next == linkedlist->tail) break;
        pointer = pointer->next;
    }
    node_t* last = pointer->next;
    pointer->next = NULL;

    linkedlist->tail = pointer;
    linkedlist->size--;

    return last;
}

/**
 * @brief function to get the node at index
 * @param linkedlist: the linkedlist to get
 * @param index: the index of the node
 * @return: node_t* || NULL
 */
node_t* get(linkedlist_t* linkedlist, int index) {
    if (!linkedlist || (index < 0 || index > linkedlist->size)) return NULL;

    int count = 0;
    node_t* pointer = linkedlist->head;
    while (pointer) {
        if (count == index)
            return pointer;
        count++;
        pointer = pointer->next;
    }
    return NULL;
}


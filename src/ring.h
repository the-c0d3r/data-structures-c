#ifndef DATA_STRUCTURES_RING_H
#define DATA_STRUCTURES_RING_H

#include <stdio.h>
#include <stdlib.h>
#include <f2fs_fs.h>

typedef struct {
    void *data;
} ring_slot_t;

typedef struct {
    size_t size;
    size_t read_head;
    size_t write_head;
    ring_slot_t *slots;
} ring_t;


// slot in a new slot
bool enqueue(ring_t *ring, void *data);

// unslot an item
void * dequeue(ring_t *ring);

// create a new ring with size
ring_t *create_ring(int size);

// destroy the ring
void destroy_ring(ring_t *ring);


#endif //DATA_STRUCTURES_RING_H

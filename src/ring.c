#include <stdbool.h>
#include "ring.h"


ring_t *create_ring(int size) {
    ring_t* ring = malloc(sizeof(ring_t));

    if (!ring) {
        perror("Unable to allocate memory for ring\n");
        exit(1);
    }

    ring->size = size;
    ring->slots = malloc(sizeof(ring_slot_t) * size);
    ring->read_head = 0;
    ring->write_head = 0;

    if (!ring->slots) {
        perror("Unable to allocate memory for ring slots\n");
        exit(1);
    }
    return ring;
}

void destroy_ring(ring_t *ring) {
    if (ring) {
        if (ring->slots)
            free(ring->slots);
        free(ring);
    }
}

bool enqueue(ring_t *ring, void *data) {
    if (!ring) {
        perror("Ring is not accessible\n");
        exit(1);
    }

    ring->slots[ring->write_head].data = data;
    ring->write_head = (ring->write_head + 1) % ring->size;
    return true;
}

void * dequeue(ring_t *ring) {
    if (!ring) {
        perror("Ring is not accessible\n");
        exit(1);
    }

    void *data = ring->slots[ring->read_head].data;
    ring->read_head= (ring->read_head + 1) % ring->size;
    return data;
}

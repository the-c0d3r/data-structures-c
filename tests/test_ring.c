#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdbool.h>

#include "../src/ring.h"


static void test_init(void **state) {
    ring_t* ring = create_ring(10);
    assert_non_null(ring);
    assert_int_equal(ring->size, 10);
    destroy_ring(ring);
}

static void test_enqueue_dequeue(void **state) {
    ring_t* ring = create_ring(10);
    void *data = {"TEST"};
    bool result = enqueue(ring, data);
    assert_int_equal(result, true);

    void *result_data = dequeue(ring);
    assert_ptr_equal(data, result_data);

    destroy_ring(ring);
}

static void test_rotate(void **state) {
    ring_t* ring = create_ring(3);

    char arr[3][6] = {
        {"test1"},
        {"test2"},
        {"test3"}
    };

    for (int i = 0 ; i < 3; i++) {
        enqueue(ring, arr[i]);
        assert_ptr_equal(ring->slots[i].data, arr[i]);
    }

    // insert "test3" to overwrite the first slot, as rotation
    bool result = enqueue(ring, arr[2]);
    assert_int_equal(result, true);

    // check if "test3" is inside the slot 0 after rotating
    assert_ptr_equal(ring->slots[0].data, arr[2]);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_init),
        cmocka_unit_test(test_enqueue_dequeue),
        cmocka_unit_test(test_rotate)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}



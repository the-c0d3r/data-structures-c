#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/bubblesort.h"


static void test_bubblesort(void **state) {
    int array[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n = 10;
    bubblesort(array, n);

    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // for each element in array, check with expected values
    for (int i = 0; i < n; i++) {
        assert_int_equal(array[i], expected[i]);
    }
}

static void test_swap(void **state) {
    int array[] = {1, 2};
    swap(&array[0], &array[1]);

    assert_int_equal(array[0], 2);
    assert_int_equal(array[1], 1);
}


int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_swap),
        cmocka_unit_test(test_bubblesort),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}



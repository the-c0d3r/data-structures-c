#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/stack.h"


static void test_init(void **state) {
    stack_t *stack = create_stack(1);
    assert_non_null(stack);
    assert_int_equal(stack->max_size, 1);
    destroy_stack(stack);
}

static void test_push(void **state) {
    stack_t *stack = create_stack(1);
    int ret = push(stack, "test");

    assert_int_equal(ret, 0);
    destroy_stack(stack);
}

static void test_push_limit(void **state) {
    stack_t *stack = create_stack(5);
    for (int i=0; i<5; i++)
        push(stack, "test");

    int ret = push(stack, "should-fail");

    assert_int_equal(ret, 1);
    // Check for push fail, overlimit

    assert_int_equal(stack->size, 5);
    assert_int_equal(stack->max_size, 5);
    destroy_stack(stack);
}

static void test_pop(void **state) {
    stack_t *stack = create_stack(1);
    push(stack, "test");
    char *ret = pop(stack);

    assert_string_equal(ret, "test");

    if (ret)
        free(ret);
    destroy_stack(stack);
}

static void test_pop_limit(void **state) {
    stack_t *stack = create_stack(1);
    push(stack, "test");
    char *ret = pop(stack);
    assert_string_equal(ret, "test");

    if (ret)
        free(ret);

    ret = pop(stack);
    assert_null(ret);
    assert_int_equal(stack->size, 0);
    destroy_stack(stack);
}

static void test_push_pop(void **state) {
    stack_t *stack = create_stack(2);
    push(stack, "test1");
    push(stack, "test2");

    char *ret = pop(stack);
    assert_string_equal(ret, "test2");
    free(ret);

    push(stack, "test3");
    ret = pop(stack);
    assert_string_equal(ret, "test3");
    free(ret);

    ret = pop(stack);
    assert_string_equal(ret, "test1");
    free(ret);

    destroy_stack(stack);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_init),
        cmocka_unit_test(test_push),
        cmocka_unit_test(test_push_limit),
        cmocka_unit_test(test_pop),
        cmocka_unit_test(test_pop_limit),
        cmocka_unit_test(test_push_pop)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}



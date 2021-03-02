#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/linkedlist.h"

static void test_node(void** state) {
    // creates a node node
    node_t* node;
    node = create_node(0);

    assert_non_null(node);
    assert_int_equal(node->value, 0);
    destroy_node(node);
}

static void test_create_linkedlist(void** state) {
    // create linkedlist
    linkedlist_t* linkedlist = create_linkedlist();
    assert_non_null(linkedlist);
    assert_null(linkedlist->head);
    assert_null(linkedlist->tail);
    assert_int_equal(linkedlist->size, 0);
    destroy(linkedlist);
}

static void test_insert_single(void** state) {
    // create linkedlist
    linkedlist_t* linkedlist = create_linkedlist();
    node_t* node = create_node(0);

    int fail = insert(NULL, node);
    assert_int_equal(fail, 1);

    int ret = insert(linkedlist, node);
    assert_int_equal(ret, 0);

    assert_non_null(linkedlist->head);
    assert_non_null(linkedlist->tail);
    assert_int_equal(linkedlist->size, 1);
    assert_ptr_equal(linkedlist->head, node);
    destroy(linkedlist);
}

static void test_insert_bulk(void** state) {
    // create linkedlist
    linkedlist_t* linkedlist = create_linkedlist();
    node_t* node1 = create_node(0);
    node_t* node2 = create_node(1);

    insert(linkedlist, node1);
    insert(linkedlist, node2);

    assert_ptr_equal(linkedlist->head, node1);
    assert_ptr_equal(linkedlist->tail, node2);
    destroy(linkedlist);
}

static void test_delete_head(void** state) {
    // create linkedlist
    linkedlist_t* linkedlist = create_linkedlist();
    node_t* node1 = create_node(0);
    node_t* node2 = create_node(0);

    insert(linkedlist, node1);
    insert(linkedlist, node2);

    int ret = delete(linkedlist, node1);

    assert_int_equal(ret, 0);
    assert_ptr_equal(linkedlist->head, node2);
    assert_ptr_equal(linkedlist->tail, node2);
    assert_int_equal(linkedlist->size, 1);
    destroy(linkedlist);
}

static void test_delete_last(void** state) {
    // create linkedlist
    linkedlist_t* linkedlist = create_linkedlist();
    node_t* node1 = create_node(0);
    node_t* node2 = create_node(0);

    insert(linkedlist, node1);
    insert(linkedlist, node2);

    int ret = delete(linkedlist, node2);

    assert_int_equal(ret, 0);
    assert_ptr_equal(linkedlist->head, node1);
    assert_ptr_equal(linkedlist->tail, node1);
    assert_int_equal(linkedlist->size, 1);
    destroy(linkedlist);
}

static void test_delete_mid(void** state) {
    // create linkedlist
    linkedlist_t* linkedlist = create_linkedlist();
    node_t* node1 = create_node(0);
    node_t* node2 = create_node(0);
    node_t* node3 = create_node(0);

    insert(linkedlist, node1);
    insert(linkedlist, node2);
    insert(linkedlist, node3);

    int ret = delete(linkedlist, node2);

    assert_int_equal(ret, 0);
    assert_ptr_equal(linkedlist->head, node1);
    assert_ptr_equal(linkedlist->tail, node3);
    assert_int_equal(linkedlist->size, 2);
    destroy(linkedlist);
}

static void test_pop_head(void** state) {
    // create linkedlist
    linkedlist_t* linkedlist = create_linkedlist();
    node_t* node1 = create_node(0);

    insert(linkedlist, node1);
    node_t* popped = pop(linkedlist);
    assert_null(linkedlist->head);
    assert_null(linkedlist->tail);
    assert_ptr_equal(popped, node1);
    assert_int_equal(linkedlist->size, 0);
    destroy_node(popped);
    destroy(linkedlist);
}

static void test_pop_last(void** state) {
    // create linkedlist
    linkedlist_t* linkedlist = create_linkedlist();
    node_t* node1 = create_node(0);
    node_t* node2 = create_node(0);

    insert(linkedlist, node1);
    insert(linkedlist, node2);

    node_t* popped = pop(linkedlist);

    assert_ptr_equal(popped, node2);
    assert_ptr_equal(linkedlist->head, node1);
    assert_ptr_equal(linkedlist->tail, node1);
    assert_int_equal(linkedlist->size, 1);
    destroy_node(popped);
    destroy(linkedlist);
}

static void test_get(void** state) {
    // create linkedlist
    linkedlist_t* linkedlist = create_linkedlist();
    node_t* node1 = create_node(0);
    node_t* node2 = create_node(0);

    insert(linkedlist, node1);
    insert(linkedlist, node2);

    node_t* get0 = get(linkedlist, 0);
    node_t* get1 = get(linkedlist, 1);

    assert_int_equal(linkedlist->size, 2);
    assert_ptr_equal(node1, get0);
    assert_ptr_equal(node2, get1);
    destroy(linkedlist);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_node),
        cmocka_unit_test(test_create_linkedlist),
        cmocka_unit_test(test_insert_single),
        cmocka_unit_test(test_insert_bulk),
        cmocka_unit_test(test_delete_head),
        cmocka_unit_test(test_delete_last),
        cmocka_unit_test(test_delete_mid),
        cmocka_unit_test(test_pop_head),
        cmocka_unit_test(test_pop_last),
        cmocka_unit_test(test_get)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

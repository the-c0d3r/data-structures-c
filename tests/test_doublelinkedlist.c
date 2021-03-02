#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/doublelinkedlist.h"

static void test_node(void** state) {
    // creates a node node
    node_t* node;
    node = create_node(0);

    assert_non_null(node);
    assert_int_equal(node->value, 0);
    destroy_node(node);
}

static void test_create_linkedlist(void** state) {
    // create dlinkedlist
    double_linkedlist_t* dlinkedlist = create_double_linkedlist();
    assert_non_null(dlinkedlist);
    assert_null(dlinkedlist->head);
    assert_null(dlinkedlist->tail);
    assert_int_equal(dlinkedlist->size, 0);
    destroy(dlinkedlist);
}

static void test_insert_single(void** state) {
    // create dlinkedlist
    double_linkedlist_t* dlinkedlist = create_double_linkedlist();
    node_t* node = create_node(0);

    int fail = insert(NULL, node);
    assert_int_equal(fail, 1);

    int ret = insert(dlinkedlist, node);
    assert_int_equal(ret, 0);

    assert_non_null(dlinkedlist->head);
    assert_non_null(dlinkedlist->tail);
    assert_int_equal(dlinkedlist->size, 1);
    assert_ptr_equal(dlinkedlist->head, node);
    destroy(dlinkedlist);
}

static void test_insert_bulk(void** state) {
    // create dlinkedlist
    double_linkedlist_t* dlinkedlist = create_double_linkedlist();
    node_t* node1 = create_node(0);
    node_t* node2 = create_node(1);

    insert(dlinkedlist, node1);
    insert(dlinkedlist, node2);

    assert_ptr_equal(dlinkedlist->head, node1);
    assert_ptr_equal(dlinkedlist->tail, node2);

    assert_ptr_equal(dlinkedlist->head->next, node2);
    assert_ptr_equal(dlinkedlist->tail->prev, node1);
    destroy(dlinkedlist);
}

static void test_delete_head(void** state) {
    // create dlinkedlist
    double_linkedlist_t* dlinkedlist = create_double_linkedlist();
    node_t* node1 = create_node(0);
    node_t* node2 = create_node(0);

    insert(dlinkedlist, node1);
    insert(dlinkedlist, node2);

    int ret = delete(dlinkedlist, node1);

    assert_int_equal(ret, 0);
    assert_ptr_equal(dlinkedlist->head, node2);
    assert_ptr_equal(dlinkedlist->tail, node2);
    assert_int_equal(dlinkedlist->size, 1);
    destroy(dlinkedlist);
}

static void test_delete_last(void** state) {
    // create dlinkedlist
    double_linkedlist_t* dlinkedlist = create_double_linkedlist();
    node_t* node1 = create_node(0);
    node_t* node2 = create_node(0);

    insert(dlinkedlist, node1);
    insert(dlinkedlist, node2);

    int ret = delete(dlinkedlist, node2);

    assert_int_equal(ret, 0);
    assert_ptr_equal(dlinkedlist->head, node1);
    assert_ptr_equal(dlinkedlist->tail, node1);
    assert_int_equal(dlinkedlist->size, 1);

    destroy(dlinkedlist);
}

static void test_delete_mid(void** state) {
    // create dlinkedlist
    double_linkedlist_t* dlinkedlist = create_double_linkedlist();
    node_t* node1 = create_node(0);
    node_t* node2 = create_node(0);
    node_t* node3 = create_node(0);

    insert(dlinkedlist, node1);
    insert(dlinkedlist, node2);
    insert(dlinkedlist, node3);

    int ret = delete(dlinkedlist, node2);

    assert_int_equal(ret, 0);
    assert_ptr_equal(dlinkedlist->head, node1);
    assert_ptr_equal(dlinkedlist->head->next, node3);
    assert_ptr_equal(dlinkedlist->tail, node3);
    assert_ptr_equal(dlinkedlist->tail->prev, node1);
    assert_int_equal(dlinkedlist->size, 2);
    destroy(dlinkedlist);
}

static void test_pop_head(void** state) {
    // create dlinkedlist
    double_linkedlist_t* dlinkedlist = create_double_linkedlist();
    node_t* node1 = create_node(0);

    insert(dlinkedlist, node1);
    node_t* popped = pop(dlinkedlist);
    assert_null(dlinkedlist->head);
    assert_null(dlinkedlist->tail);
    assert_ptr_equal(popped, node1);
    assert_int_equal(dlinkedlist->size, 0);
    destroy_node(popped);
    destroy(dlinkedlist);
}

static void test_pop_last(void** state) {
    // create dlinkedlist
    double_linkedlist_t* dlinkedlist = create_double_linkedlist();
    node_t* node1 = create_node(0);
    node_t* node2 = create_node(0);

    insert(dlinkedlist, node1);
    insert(dlinkedlist, node2);

    node_t* popped = pop(dlinkedlist);

    assert_ptr_equal(popped, node2);
    assert_ptr_equal(dlinkedlist->head, node1);
    assert_ptr_equal(dlinkedlist->tail, node1);
    assert_int_equal(dlinkedlist->size, 1);
    destroy_node(popped);
    destroy(dlinkedlist);
}

static void test_get(void** state) {
    // create dlinkedlist
    double_linkedlist_t* dlinkedlist = create_double_linkedlist();
    node_t* node1 = create_node(0);
    node_t* node2 = create_node(0);

    insert(dlinkedlist, node1);
    insert(dlinkedlist, node2);

    node_t* get0 = get(dlinkedlist, 0);
    node_t* get1 = get(dlinkedlist, 1);

    assert_int_equal(dlinkedlist->size, 2);
    assert_ptr_equal(node1->next, node2);
    assert_ptr_equal(node2->prev, node1);
    assert_ptr_equal(node1, get0);
    assert_ptr_equal(node2, get1);
    destroy(dlinkedlist);
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

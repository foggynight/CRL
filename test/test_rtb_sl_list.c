/* --- test_rtb_sl_list.c ---
 *
 * Target: rtb_list.h v0.0.0
 * First Commit: 2020-12-22
 * Last Updated: 2020-12-29
 *
 * Copyright (C) 2020 Robert Coffey
 * Released under the MIT license */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define RTB_DEFINE
#include "rtb_list.h"

#define NODE_COUNT 3

/* test_sl_fill: Fill the list with values: [0, ... NODE_COUNT-1]
 * @param list List to fill */
static void test_sl_fill(sl_list_t *list);

/* test_sl_sorted_p: Check if a singly linked list is sorted in
 *     ascending order.
 * @param list List to check
 * @return Non-zero if list is sorted */
static int test_sl_sorted_p(sl_list_t *list);

/* Test procedures */
static void test_sl_node(void);
static void test_sl_list(void);
static void test_sl_stack(void);
static void test_sl_queue(void);

int main(void)
{
    assert(NODE_COUNT >= 3); // Test cases require at least three nodes

    test_sl_node();
    test_sl_list();
    test_sl_stack();
    test_sl_queue();

    puts("test_rtb_sl_list.c: All tests passed");
    return 0;
}

static void test_sl_fill(sl_list_t *list)
{
    assert(list && !list->head && !list->tail);
    assert(sl_node_c(list) == 0);

    sl_node_t *original_head = NULL;
    for (int i = 0; i < NODE_COUNT; ++i) {
        sl_node_t *node = sl_create_node();

        int *val = (int *)malloc(sizeof(int));
        assert(val);
        *val = i;

        node->val = val;
        sl_append(list, node);

        if (!original_head)
            original_head = node;
        assert(list->head == original_head);
        assert(list->tail == node);
    }

    assert(list && list->head && list->tail);
    assert(sl_node_c(list) == NODE_COUNT);
}

static int test_sl_sorted_p(sl_list_t *list)
{
    for (sl_node_t *walk = list->head; walk; walk = walk->next) {
        if (!walk->next)
            return 1;
        else if (*(int *)walk->val > *(int *)walk->next->val)
            return 0;
    }
    return 1;
}

static void test_sl_node(void)
{
    sl_node_t *node = sl_create_node();
    assert(node && !node->val && !node->next);

    node = sl_destroy_node(node);
    assert(!node);

    puts("test_rtb_sl_list.c: Singly linked node tests passed");
}

static void test_sl_list(void)
{
    /* Create list */
    sl_list_t *list = sl_create_list();
    assert(list && sl_empty_p(list));

    /* Fill the list using a test function */
    test_sl_fill(list);
    assert(!sl_empty_p(list));

    /* Test list values */
    sl_node_t *walk = list->head;
    for (int i = 0; i < NODE_COUNT; ++i) {
        assert(walk && *(int *)walk->val == i);
        walk = walk->next;
    }

    /* Consume the list head-first */
    for (sl_node_t *head = list->head; head; head = list->head) {
        assert(*(int *)head->val == *(int *)list->head->val);
        sl_node_t *expected_head = head->next;
        sl_remove(list, list->head, 1);
        assert(list->head == expected_head);
    }
    test_sl_fill(list);

    /* Consume the list tail-first */
    for (sl_node_t *tail = list->tail; tail; tail = list->tail) {
        sl_node_t *expected_tail;
        if (list->head == list->tail)
            expected_tail = NULL;
        else
            for (expected_tail = list->head;
                 expected_tail->next != list->tail;
                 expected_tail = expected_tail->next);
        sl_remove(list, list->tail, 1);
        assert(list->tail == expected_tail);
        if (list->tail)
            assert(list->tail->next == NULL);
    }
    test_sl_fill(list);

    /* Remove a node in the list body */
    sl_remove(list, list->head->next, 1);
    assert(list->head && list->tail);
    assert(*(int *)list->head->val + 2 == *(int *)list->head->next->val);

    /* Remove a node using its index */
    sl_node_t *new_head = list->head->next;
    sl_remove_at(list, 0, 1);
    assert(list->head == new_head);

    /* Empty the list */
    while (!sl_empty_p(list))
        sl_remove(list, list->head, 1);
    test_sl_fill(list);

    /* Get nodes by index */
    assert(sl_get_node(list, 0) == list->head);
    assert(sl_get_node(list, 1) == list->head->next);
    assert(sl_get_node(list, NODE_COUNT) == NULL);

    /* Get indices of nodes */
    assert(sl_get_index(list, list->head) == 0);
    assert(sl_get_index(list, list->tail) == NODE_COUNT-1);
    sl_node_t *node = sl_create_node();
    assert(sl_get_index(list, node) == -1);
    sl_append(list, node);
    assert(sl_get_index(list, node) == NODE_COUNT);
    assert(sl_get_index(list, list->tail) == NODE_COUNT);

    /* Reset the list */
    sl_destroy_list(&list);
    assert(!list);
    list = sl_create_list();
    assert(list);

    /* Insert values out of order: [0, 1, 2, 3, 4] */
    int list_values[] = {2, 0, 1, 5, 4};
    for (int i = 0; i < 3; ++i) {
        node = sl_create_node();
        assert(node);

        int *val = (int *)malloc(sizeof(int));
        assert(val);
        *val = list_values[i];
        node->val = val;

        switch(i) {
            case 0: sl_insert(list, node, 1); break; // Insert at index greater than size of list
            case 1: sl_insert(list, node, 0); break; // Insert at beginning of list
            case 2: sl_insert(list, node, 1); break; // Insert in list body
            case 3: sl_insert(list, node, 3); break; // Insert at end of list
            case 4: sl_insert(list, node, 3); break; // Insert in list body
        }

        assert(test_sl_sorted_p(list)); // Test list values
    }

    assert(sl_node_c(list) > 1);
    sl_node_t *replacement_node;
    sl_node_t *second_node;

    /* Replace a node using a pointer to it */
    replacement_node = sl_create_node();
    second_node = list->head->next;
    sl_replace(list, list->head, replacement_node);
    assert(list->head == replacement_node);
    assert(list->head->next == second_node);

    /* Replace a node using its index */
    replacement_node = sl_create_node();
    second_node = list->head->next;
    sl_replace_at(list, 0, replacement_node);
    assert(list->head == replacement_node);
    assert(list->head->next == second_node);

    /* Destroy the list */
    assert(list);
    assert(!sl_empty_p(list));
    sl_destroy_list(&list);
    assert(!list);

    puts("test_rtb_sl_list.c: Singly linked list tests passed");
}

static void test_sl_stack(void)
{
    sl_list_t *list = sl_create_list();
    assert(list);

    for (int i = 0; i < NODE_COUNT; ++i) {
        sl_node_t *node = sl_create_node();
        assert(node);

        int *val = (int *)malloc(sizeof(int));
        assert(val);
        *val = i;
        node->val = val;

        sl_push(list, node);
        assert(test_sl_sorted_p(list)); // Test list values
    }

    sl_node_t *node = sl_create_node();
    assert(node);

    int *val = (int *)malloc(sizeof(int));
    assert(val);
    *val = 0;
    node->val = val;

    sl_push(list, node);
    assert(!test_sl_sorted_p(list)); // Test list values

    assert(sl_pop(list) == node);
    assert(test_sl_sorted_p(list)); // Test list values

    sl_destroy_node(node);

    /* Destroy the list */
    sl_destroy_list(&list);
    assert(!list);

    puts("test_rtb_sl_list.c: Singly linked stack tests passed");
}

static void test_sl_queue(void)
{
    sl_list_t *list = sl_create_list();
    assert(list);

    for (int i = NODE_COUNT-1; i >= 0; --i) {
        sl_node_t *node = sl_create_node();
        assert(node);

        int *val = (int *)malloc(sizeof(int));
        assert(val);
        *val = i;
        node->val = val;

        sl_enque(list, node);
        assert(test_sl_sorted_p(list)); // Test list values
    }

    sl_node_t *node = sl_create_node();
    assert(node);

    int *val = (int *)malloc(sizeof(int));
    assert(val);
    *val = NODE_COUNT;
    node->val = val;

    sl_enque(list, node);
    assert(!test_sl_sorted_p(list)); // Test list values

    sl_deque(list);
    assert(!test_sl_sorted_p(list)); // Test list values

    /* Destroy the list */
    sl_destroy_list(&list);
    assert(!list);

    puts("test_rtb_sl_list.c: Singly linked queue tests passed");
}

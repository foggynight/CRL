/* --- test_rtb_list.c ---
 *
 * Target: rtb_list.h v0.6.x
 * First Commit: 2020-12-22
 * Last Updated: 2020-12-24
 *
 * Copyright (C) 2020 Robert Coffey
 * Released under the MIT license */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define RTB_DEFINE
#include "rtb_list.h"

#define NODE_COUNT 3

/* populate_list: Fill the list with values: [0, ... NODE_COUNT-1]
 * @param list List to fill */
static void populate_list(sl_list_t *list);

/* list_is_sorted: Check if a list is sorted in ascending order.
 * @param list List to check
 * @return Non-zero if list is sorted */
static int list_is_sorted(sl_list_t *list);

int main(void)
{
    assert(NODE_COUNT >= 3); // Test cases require at least three nodes

    /* Test node functions */
    sl_node_t *node = sl_create_node();
    assert(node);
    assert(!node->val && !node->next);
    node = sl_destroy_node(node);
    assert(!node);

    /* Create and populate list */
    sl_list_t *list = sl_create_list();
    assert(!list->head && !list->tail);
    populate_list(list);
    assert(list->head && list->tail);

    /* Test list values */
    sl_node_t *walk = list->head;
    for (int i = 0; i < NODE_COUNT; ++i) {
        assert(walk);
        assert(*(int *)walk->val == i);
        walk = walk->next;
    }

    /* Consume the list head-first */
    for (sl_node_t *head = list->head; head; head = list->head) {
        int node_value = *(int *)head->val;
        int expected_value = *(int *)list->head->val;
        assert(node_value == expected_value);

        sl_node_t *expected_head = head->next;
        sl_remove_node(list, list->head);
        assert(list->head == expected_head);
    }
    populate_list(list);

    /* Consume the list tail-first */
    for (sl_node_t *tail = list->tail; tail; tail = list->tail) {
        int node_value = *(int *)tail->val;
        int expected_value = *(int *)list->tail->val;
        assert(node_value == expected_value);

        sl_node_t *expected_tail;
        if (list->head == list->tail) {
            expected_tail = NULL;
        }
        else {
            for (expected_tail = list->head;
                 expected_tail->next != list->tail;
                 expected_tail = expected_tail->next);
         }

        sl_remove_node(list, list->tail);
        assert(list->tail == expected_tail);
        if (list->tail)
            assert(list->tail->next == NULL);
    }
    populate_list(list);

    /* Remove a node in the list body */
    sl_remove_node(list, list->head->next);
    assert(list->head && list->tail);
    assert(*(int *)list->head->val + 2 == *(int *)list->head->next->val);

    /* Get nodes by index */
    assert(sl_get_node(list, 0) == list->head);
    assert(sl_get_node(list, 1) == list->tail);

    /* Empty the list */
    assert(list);
    sl_destroy_list(list);
    assert(list);
    assert(!list->head && !list->tail);

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
            case 0: sl_insert_node(list, node, 1); break; // Insert at index greater than size of list
            case 1: sl_insert_node(list, node, 0); break; // Insert at the beginning of the list
            case 2: sl_insert_node(list, node, 1); break; // Insert in the list body
            case 3: sl_insert_node(list, node, 3); break; // Insert at the end of list
            case 4: sl_insert_node(list, node, 3); break; // Insert in the list body
        }

        /* Test list values */
        assert(list_is_sorted(list));
    }

    /* Destroy the list */
    assert(list);
    list = sl_destroy_list(list);
    assert(!list);

    puts("test_rtb_list.c: All tests passed");
    return 0;
}

static void populate_list(sl_list_t *list)
{
    assert(list);
    assert(!list->head && !list->tail);

    sl_node_t *original_head = NULL;
    for (int i = 0; i < NODE_COUNT; ++i) {
        sl_node_t *node = sl_create_node();

        if (!list->head)
            original_head = node;

        int *val = (int *)malloc(sizeof(int));
        assert(val);
        *val = i;

        node->val = val;
        sl_append_node(list, node);

        assert(list->head == original_head);
        assert(list->tail == node);
    }

    if (NODE_COUNT > 0)
        assert(list->head && list->tail);
}

static int list_is_sorted(sl_list_t *list)
{
    for (sl_node_t *walk = list->head; walk; walk = walk->next) {
        if (!walk->next)
            return 1;
        else if (*(int *)walk->val > *(int *)walk->next->val)
            return 0;
    }
    return 1;
}

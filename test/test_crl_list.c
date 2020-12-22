/* --- test_crl_list.c ---
 *
 * Target: crl_list.h v0.4.x
 * First Commit: 2020-12-22
 * Last Updated: 2020-12-22
 *
 * Copyright (C) 2020 Robert Coffey
 * Released under the MIT license */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define CRL_DEFINE
#include "crl_list.h"

#define NODE_COUNT 3

/* populate_list: Fill the list with values: [0, ... NODE_COUNT-1]
 * @param list List to fill */
static void populate_list(sl_list_t *list);

int main(void)
{
    assert(NODE_COUNT >= 3); // Test cases require at least three nodes

    /* Test node functions */
    sl_node_t *node = sl_create_node();
    assert(node);
    node = sl_destroy_node(node);
    assert(!node);

    /* Create and populate list */
    sl_list_t *list = sl_create_list();
    populate_list(list);

    /* Test list values */
    int expected_value = 0;
    for (sl_node_t *walk = list->head; walk; walk = walk->next) {
        int node_value = *(int *)walk->val;
        assert(node_value == expected_value);
        ++expected_value;
    }

    /* Consume the list head-first */
    for (sl_node_t *head = list->head; head; head = list->head) {
        int node_value = *(int *)head->val;
        expected_value = *(int *)list->head->val;
        sl_node_t *expected_head = head->next;
        assert(node_value == expected_value);

        free(list->head->val);
        sl_remove_node(list, list->head);

        assert(list->head == expected_head);
    }
    populate_list(list);

    /* Consume the list tail-first */
    for (sl_node_t *tail = list->tail; tail; tail = list->tail) {
        int node_value = *(int *)tail->val;
        expected_value = *(int *)list->tail->val;
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

        free(list->tail->val);
        sl_remove_node(list, list->tail);

        assert(list->tail == expected_tail);
        if (list->tail)
            assert(list->tail->next == NULL);
    }
    populate_list(list);

    /* Remove node in the list body */
    free(list->head->next->val);
    sl_remove_node(list, list->head->next);
    assert(list->head && list->tail);
    assert(*(int *)list->head->val + 2 == *(int *)list->head->next->val);

    /* Empty the list */
    sl_destroy_list(list);
    assert(!list->head && !list->tail);

    /* Destroy the list */
    assert(list);
    list = sl_destroy_list(list);
    assert(!list);

    puts("test_crl_list.c: All tests passed");
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
        sl_add_node(list, node);

        assert(list->head == original_head);
        assert(list->tail == node);
    }

    if (NODE_COUNT > 0)
        assert(list->head && list->tail);
}

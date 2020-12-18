/* --- list_single_link_test.c ---
 *
 * This file is part of the crl library.
 *
 * Test Target: list/single_link.h v0.1.0
 *
 * File Version: 0.1.0
 * Last Updated: 2020-12-17
 *
 * Copyright (C) 2020 Robert Coffey
 * Released under the GPLv2 license */

#include <assert.h>
#include <stdlib.h>

#include "../list/single_link.h"

#define LIST_LENGTH 3 // Must be greater than or equal to 3 for test cases

void fill_list(sl_node_t **head, sl_node_t **tail);

int main(void)
{
    sl_node_t *head, *tail, *walk;
    head = tail = NULL;

    /* Testing creating and destroying a node */
    walk = sl_create_node();
    assert(walk);
    assert(!walk->next);
    sl_destroy_node(walk);
    walk = NULL;

    /* Test creating a list */
    fill_list(&head, &tail);
    walk = head;
    for (int i = 0; i < LIST_LENGTH; ++i) {
        assert(*(int *)(walk->val) == i);
        walk = walk->next;
    }
    assert(!walk);

    /* Test destroying a list head first */
    for (int i = 0; i < LIST_LENGTH; ++i) {
        assert(head);
        assert(tail);
        sl_remove_node(&head, &tail, head);
    }
    assert(!head);
    assert(!tail);

    /* Test destroying a list tail first */
    fill_list(&head, &tail);
    for (int i = 0; i < LIST_LENGTH; ++i) {
        assert(head);
        assert(tail);
        sl_remove_node(&head, &tail, tail);
    }
    assert(!head);
    assert(!tail);

    /* Test removing an element in the middle of the list */
    fill_list(&head, &tail);
    sl_node_t *target = head->next->next;
    sl_remove_node(&head, &tail, head->next);
    assert(head->next == target);

    puts("list_single_link_test.c: All tests passed");
    return 0;
}

void fill_list(sl_node_t **head, sl_node_t **tail)
{
    assert(!*head);
    assert(!*tail);
    for (int i = 0; i < LIST_LENGTH; ++i) {
        int *val = malloc(sizeof(int));
        assert(val);
        *val = i;

        sl_node_t *new_node = sl_create_node();
        new_node->val = val;

        sl_add_node(head, tail, new_node);
        assert(*head);
        assert(*tail);
    }
}

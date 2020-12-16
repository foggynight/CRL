/* --- list/single_link.h ---
 *
 * Generic singly linked list implementation.
 *
 * Copyright (C) 2020 Robert Coffey
 * Licensed under the GNU GPLv2 */

#ifndef CRL_LIST_SINGLE_LINK_H_
#define CRL_LIST_SINGLE_LINK_H_

#include <stdio.h>
#include <stdlib.h>

/* sl_node_t: Singly linked list node. */
typedef struct sl_node {
    void *val;            // Pointer to the node value
    struct sl_node *next; // Pointer to the next node
} sl_node_t;

/** sl_create_node: Create a singly linked list node.
 * @return {sl_node_t *}: Pointer to the new node */
sl_node_t *sl_create_node(void);

/** sl_destroy_node: Destroy a singly linked list node.
 * @param target {sl_node_t *}: Pointer to the target node */
void sl_destroy_node(sl_node_t *target);

sl_node_t *sl_create_node(void)
{
    sl_node_t *new_node = calloc(1, sl_node_t);
    if (!new_node) {
        fputs("list/single_link.h: Error: create_node failed\n", stderr);
        exit(1);
    }
    return new_node;
}

void sl_destroy_node(sl_node_t *target)
{
    if (!target) {
        fputs("list/single_link.h: Error: destroy_node failed\n", stderr);
        exit(1);
    }
    free(target);
}

#endif

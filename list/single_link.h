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
 * @param node {sl_node_t *}: Pointer to the target node */
void sl_destroy_node(sl_node_t *node);

/** sl_add_node: Add a node to a singly linked list.
 * @param head {sl_node_t **}: Pointer to a pointer to the head of the list
 * @param tail {sl_node_t **}: Pointer to a pointer to the tail of the list
 * @param node {sl_node_t *}:  Pointer to the node to add to the list */
void sl_add_node(sl_node_t **head, sl_node_t **tail, sl_node_t *node);

sl_node_t *sl_create_node(void)
{
    sl_node_t *node = calloc(1, sl_node_t);
    if (!node) {
        fputs("list/single_link.h: Error: create_node failed\n", stderr);
        exit(EXIT_FAILED);
    }
    return node;
}

void sl_destroy_node(sl_node_t *node)
{
    if (!node) {
        fputs("list/single_link.h: Error: destroy_node failed\n", stderr);
        exit(EXIT_FAILED);
    }
    free(node);
}

void sl_add_node(sl_node_t **head, sl_node_t **tail, sl_node_t *node)
{
    /* Invalid list initialization */
    if ((*head && !*tail)
     || (!*head && *tail) {
        fputs("list/single_link.h: Error: Invalid list initialization\n", stderr);
        exit(EXIT_FAILED);
    }

    /* List is empty */
    if (!*head) {
        *head = *tail = node;
    }
    /* List is not empty */
    else {
        (*tail)->next = node;
        *tail = node;
    }
}

#endif

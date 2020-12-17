/* --- single_link.h ---
 *
 * Generic singly linked list implementation, requires a head and tail
 * pointer which are to be initialized to NULL.
 *
 * File Version: 0.1.0
 * Last Updated: 2020-12-17
 *
 * This file is part of the crl library:
 * https://github.com/foggynight/crl
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

/** sl_is_empty: Check if a list is empty.
 * @param head {sl_node_t *}: Pointer to the head of the list
 * @param tail {sl_node_t *}: Pointer to the tail of the list
 * @return {int}: Non-zero if the list is empty */
int sl_is_empty(sl_node_t *head, sl_node_t *tail);

/** sl_add_node: Add a node to a singly linked list.
 * @param head {sl_node_t **}: Pointer to a pointer to the head of the list
 * @param tail {sl_node_t **}: Pointer to a pointer to the tail of the list
 * @param node {sl_node_t *}:  Pointer to the node to add to the list */
void sl_add_node(sl_node_t **head, sl_node_t **tail, sl_node_t *node);

/** sl_remove_node: Remove a node from a singly linked list.
 * @param head {sl_node_t **}: Pointer to a pointer to the head of the list
 * @param tail {sl_node_t **}: Pointer to a pointer to the tail of the list
 * @param node {sl_node_t *}:  Pointer to the node to remove from the list */
void sl_remove_node(sl_node_t **head, sl_node_t **tail, sl_node_t *node);

#ifdef CRL_DEFINE

sl_node_t *sl_create_node(void)
{
    sl_node_t *node = calloc(1, sizeof(sl_node_t));
    if (!node) {
        fputs("list/single_link.h: Error: create_node: calloc returned NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    return node;
}

void sl_destroy_node(sl_node_t *node)
{
    if (!node) {
        fputs("list/single_link.h: Error: destroy_node: Cannot destroy NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    free(node);
}

int sl_is_empty(sl_node_t *head, sl_node_t *tail)
{
    if ((head && !tail)
     || (!head && tail)) {
        fputs("list/single_link.h: Error: sl_is_empty: Invalid list initialization\n", stderr);
        exit(EXIT_FAILURE);
    }
    return !head && !tail;
}

void sl_add_node(sl_node_t **head, sl_node_t **tail, sl_node_t *node)
{
    if (!node) {
        fputs("list/single_link.h: Error: sl_add_node: Cannot add NULL\n", stderr);
        exit(EXIT_FAILURE);
    }

    if (sl_is_empty(*head, *tail)) {
        *head = *tail = node;
    }
    else {
        (*tail)->next = node;
        *tail = node;
    }
}

void sl_remove_node(sl_node_t **head, sl_node_t **tail, sl_node_t *node)
{
    if (!node) {
        fputs("list/single_link.h: Error: sl_remove_node: Cannot remove NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (sl_is_empty(*head, *tail)) {
        fputs("list/single_link.h: Error: sl_remove_node: List is empty\n", stderr);
        exit(EXIT_FAILURE);
    }

    if (node == *head) {
        sl_node_t *old_head = *head;

        *head = (*head)->next;
        if (old_head == *tail)
            *tail = *head;

        sl_destroy_node(old_head);
    }
    else if (node == *tail) {
        sl_node_t *old_tail = *tail;

        sl_node_t *walk;
        for (walk = *head; walk->next != *tail; walk = walk->next);
        *tail = walk;
        (*tail)->next = NULL;

        sl_destroy_node(old_tail);
    }
    else {
        sl_node_t *walk;
        for (walk = *head; walk->next != node; walk = walk->next);

        sl_node_t *new_next = walk->next->next;
        sl_destroy_node(walk->next);

        walk->next = new_next;
    }
}

#endif // CRL_DEFINE
#endif // CRL_LIST_SINGLE_LINK_H_

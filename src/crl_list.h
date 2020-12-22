/* --- crl_list.h ---
 *
 * Generic linked list implementations.
 *
 * Define the CRL_DEFINE macro before including this file to define
 * these header functions.
 *
 * This file is part of the crl library:
 * https://github.com/foggynight/crl
 *
 * File Version: 0.3.2
 * First Commit: 2020-12-16
 * Last Updated: 2020-12-22
 *
 * Copyright (C) 2020 Robert Coffey
 * Released under the MIT license */

#ifndef CRL_LIST_H_
#define CRL_LIST_H_

/* sl_node_t: Singly linked node. */
typedef struct sl_node {
    void *val;            // Pointer to the node value
    struct sl_node *next; // Pointer to the next node
} sl_node_t;

/* sl_list_t: Singly linked list. */
typedef struct sl_list {
    sl_node_t *head; // Pointer to the head of the list
    sl_node_t *tail; // Pointer to the tail of the list
} sl_list_t;

/* sl_create_node: Create a singly linked list node.
 * @return Pointer to the new node */
sl_node_t *sl_create_node(void);

/* sl_destroy_node: Destroy a singly linked list node.
 * @param node Pointer to the target node
 * @return Always NULL */
sl_node_t *sl_destroy_node(sl_node_t *node);

/* sl_create_list: Create a singly linked list.
 * @return Pointer to the new list */
sl_list_t *sl_create_list(void);

/* sl_destroy_list: Destroy a singly linked list.
 * @param list Pointer to the target list
 * @return Always NULL */
sl_list_t *sl_destroy_list(sl_list_t *list);

/* sl_empty_p: Check if a singly linked list is empty.
 * @param list Pointer to the target list
 * @return Non-zero if the list is empty */
int sl_empty_p(sl_list_t *list);

/* sl_add_node: Add a node to a singly linked list.
 * @param list Pointer to the target list
 * @param node Pointer to the node to add */
void sl_add_node(sl_list_t *list, sl_node_t *node);

/* sl_remove_node: Remove a node from a singly linked list.
 * @param list Pointer to the target list
 * @param node Pointer to the node to remove */
void sl_remove_node(sl_list_t *list, sl_node_t *node);

#ifdef CRL_DEFINE

#include <stdio.h>
#include <stdlib.h>

sl_node_t *sl_create_node(void)
{
    sl_node_t *node = (sl_node_t *)calloc(1, sizeof(sl_node_t));
    if (!node) {
        fputs("list/single_link.h: Error: sl_create_node: calloc failed\n", stderr);
        exit(EXIT_FAILURE);
    }
    return node;
}

sl_node_t *sl_destroy_node(sl_node_t *node)
{
    if (!node) {
        fputs("list/single_link.h: Error: sl_destroy_node: Cannot destroy NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    free(node);
    return NULL;
}

sl_list_t *sl_create_list(void)
{
    sl_list_t *list = (sl_list_t *)calloc(1, sizeof(sl_list_t));
    if (!list) {
        fputs("list/single_link.h: Error: sl_create_list: calloc failed\n", stderr);
        exit(EXIT_FAILURE);
    }
    return list;
}

sl_list_t *sl_destroy_list(sl_list_t *list)
{
    while (!sl_is_empty(list))
        sl_remove_node(list, list->head);
    return NULL;
}

int sl_empty_p(sl_list_t *list)
{
    if ((list->head && !list->tail)
        || (!list->head && list->tail))
    {
        fputs("list/single_link.h: Error: sl_is_empty: Invalid list initialization\n", stderr);
        exit(EXIT_FAILURE);
    }
    return !list->head && !list->tail;
}

void sl_add_node(sl_list_t *list, sl_node_t *node)
{
    if (!node) {
        fputs("list/single_link.h: Error: sl_add_node: Cannot add NULL\n", stderr);
        exit(EXIT_FAILURE);
    }

    if (sl_is_empty(list)) {
        list->head = list->tail = node;
    }
    else {
        list->tail->next = node;
        list->tail = node;
    }
}

void sl_remove_node(sl_list_t *list, sl_node_t *node)
{
    if (!node) {
        fputs("list/single_link.h: Error: sl_remove_node: Cannot remove NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (sl_is_empty(list)) {
        fputs("list/single_link.h: Error: sl_remove_node: List is empty\n", stderr);
        exit(EXIT_FAILURE);
    }

    if (node == list->head) {
        sl_node_t *old_head = list->head;

        list->head = (list->head)->next;
        if (old_head == list->tail)
            list->tail = list->head;

        sl_destroy_node(old_head);
    }
    else if (node == list->tail) {
        sl_node_t *old_tail = list->tail;

        sl_node_t *walk;
        for (walk = list->head; walk->next != list->tail; walk = walk->next);
        list->tail = walk;
        list->tail->next = NULL;

        sl_destroy_node(old_tail);
    }
    else {
        sl_node_t *walk;
        for (walk = list->head; walk->next != node; walk = walk->next);

        sl_node_t *new_next = walk->next->next;
        sl_destroy_node(walk->next);

        walk->next = new_next;
    }
}

#endif // CRL_DEFINE
#endif // CRL_LIST_H_

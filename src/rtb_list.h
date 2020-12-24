/* --- rtb_list.h ---
 *
 * Generic linked list implementations.
 *
 * Define the RTB_DEFINE macro before including this header in just one
 * compilation unit of your program.
 *
 * In other compilation units, include the header as normal.
 *
 * This file is part of the rtb library:
 * https://github.com/foggynight/rtb
 *
 * File Version: 0.6.4
 * First Commit: 2020-12-16
 * Last Updated: 2020-12-24
 *
 * Copyright (C) 2020 Robert Coffey
 * Released under the MIT license */

#ifndef RTB_LIST_H_
#define RTB_LIST_H_

/* ---------------------------------------------- */
/* --- BEGIN: SINGLY LINKED LIST DECLARATIONS --- */

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

/* sl_is_empty: Check if a singly linked list is empty.
 * @param list Pointer to the target list
 * @return Non-zero if the list is empty */
int sl_is_empty(sl_list_t *list);

/* sl_append_node: Append a node to a singly linked list.
 * @param list Pointer to the target list
 * @param node Pointer to the node to add */
void sl_append_node(sl_list_t *list, sl_node_t *node);

/* sl_insert_node: Insert a node in a singly linked list.
 * @param list Pointer to the target list
 * @param node Pointer to the node to add
 * @param pos  Position to insert the node */
void sl_insert_node(sl_list_t *list, sl_node_t *node, int pos);

/* sl_remove_node: Remove a node from a singly linked list.
 * @param list Pointer to the target list
 * @param node Pointer to the node to remove */
void sl_remove_node(sl_list_t *list, sl_node_t *node);

/* sl_get_node: Get a node from a singly linked list using its index.
 * @param list  List of nodes
 * @param index Index of the node
 * @return Node at index */
sl_node_t *sl_get_node(sl_list_t *list, int index);

/* --- ENDOF: SINGLY LINKED LIST DECLARATIONS --- */
/* ---------------------------------------------- */

/* ---------------------------------------------- */
/* --- BEGIN: DOUBLY LINKED LIST DECLARATIONS --- */

/* dl_node_t: Doubly linked node. */
typedef struct dl_node {
    void *val;            // Pointer to the node value
    struct dl_node *prev; // Pointer to the previous node
    struct dl_node *next; // Pointer to the next node
} dl_node_t;

/* dl_list_t: Doubly linked list. */
typedef struct dl_list {
    dl_node_t *head; // Pointer to the head of the list
    dl_node_t *tail; // Pointer to the tail of the list
} dl_list_t;

/* dl_create_node: Create a doubly linked list node.
 * @return Pointer to the new node */
dl_node_t *dl_create_node(void);

/* dl_destroy_node: Destroy a doubly linked list node.
 * @param node Pointer to the target node
 * @return Always NULL */
dl_node_t *dl_destroy_node(dl_node_t *node);

/* dl_create_list: Create a doubly linked list.
 * @return Pointer to the new list */
dl_list_t *dl_create_list(void);

/* dl_destroy_list: Destroy a doubly linked list.
 * @param list Pointer to the target list
 * @return Always NULL */
dl_list_t *dl_destroy_list(dl_list_t *list);

/* dl_is_empty: Check if a doubly linked list is empty.
 * @param list Pointer to the target list
 * @return Non-zero if the list is empty */
int dl_is_empty(dl_list_t *list);

/* dl_append_node: Append a node to a doubly linked list.
 * @param list Pointer to the target list
 * @param node Pointer to the node to add */
void dl_append_node(dl_list_t *list, dl_node_t *node);

/* dl_insert_node: Insert a node in a doubly linked list.
 * @param list Pointer to the target list
 * @param node Pointer to the node to add
 * @param pos  Position to insert the node */
void dl_insert_node(dl_list_t *list, dl_node_t *node, int pos);

/* dl_remove_node: Remove a node from a doubly linked list.
 * @param list Pointer to the target list
 * @param node Pointer to the node to remove */
void dl_remove_node(dl_list_t *list, dl_node_t *node);

/* --- ENDOF: DOUBLY LINKED LIST DECLARATIONS --- */
/* ---------------------------------------------- */

#ifdef RTB_DEFINE

#include <stdio.h>
#include <stdlib.h>

/* --------------------------------------------- */
/* --- BEGIN: SINGLY LINKED LIST DEFINITIONS --- */

sl_node_t *sl_create_node(void)
{
    sl_node_t *node = (sl_node_t *)calloc(1, sizeof(sl_node_t));
    if (!node) {
        fputs("rtb_list.h: Error: sl_create_node: calloc failed\n", stderr);
        exit(EXIT_FAILURE);
    }
    return node;
}

sl_node_t *sl_destroy_node(sl_node_t *node)
{
    if (!node) {
        fputs("rtb_list.h: Error: sl_destroy_node: node is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (node->val)
        free(node->val);
    free(node);
    return NULL;
}

sl_list_t *sl_create_list(void)
{
    sl_list_t *list = (sl_list_t *)calloc(1, sizeof(sl_list_t));
    if (!list) {
        fputs("rtb_list.h: Error: sl_create_list: calloc failed\n", stderr);
        exit(EXIT_FAILURE);
    }
    return list;
}

sl_list_t *sl_destroy_list(sl_list_t *list)
{
    if (!list) {
        fputs("rtb_list.h: Error: sl_destroy_list: list is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    while (!sl_is_empty(list))
        sl_remove_node(list, list->head);
    return NULL;
}

int sl_is_empty(sl_list_t *list)
{
    if (!list) {
        fputs("rtb_list.h: Error: sl_is_empty: list is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if ((list->head && !list->tail)
        || (!list->head && list->tail))
    {
        fputs("rtb_list.h: Error: sl_is_empty: invalid list initialization\n", stderr);
        exit(EXIT_FAILURE);
    }
    return !list->head && !list->tail;
}

void sl_append_node(sl_list_t *list, sl_node_t *node)
{
    if (!list) {
        fputs("rtb_list.h: Error: sl_append_node: list is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (!node) {
        fputs("rtb_list.h: Error: sl_append_node: node is NULL\n", stderr);
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

void sl_insert_node(sl_list_t *list, sl_node_t *node, int pos)
{
    if (!list) {
        fputs("rtb_list.h: Error: sl_insert_node: list is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (!node) {
        fputs("rtb_list.h: Error: sl_insert_node: node is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (pos < 0) {
        fputs("rtb_list.h: Error: sl_insert_node: invalid pos\n", stderr);
        exit(EXIT_FAILURE);
    }
    else if (sl_is_empty(list)) {
        list->head = list->tail = node;
    }
    else if (pos == 0) {
        node->next = list->head;
        list->head = node;
    }
    else {
        int index = 0;
        sl_node_t *last = NULL, *walk = list->head;
        while (index < pos && walk) {
            last = walk;
            walk = walk->next;
            ++index;
        }
        last->next = node;
        node->next = walk;
        if (!walk)
            list->tail = node;
    }
}

void sl_remove_node(sl_list_t *list, sl_node_t *node)
{
    if (!list) {
        fputs("rtb_list.h: Error: sl_remove_node: list is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (!node) {
        fputs("rtb_list.h: Error: sl_remove_node: node is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (sl_is_empty(list)) {
        fputs("rtb_list.h: Error: sl_remove_node: list is empty\n", stderr);
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
        for (walk = list->head;
             walk->next != list->tail;
             walk = walk->next);
        list->tail = walk;
        list->tail->next = NULL;
        sl_destroy_node(old_tail);
    }
    else {
        sl_node_t *walk;
        for (walk = list->head;
             walk->next != node;
             walk = walk->next);
        sl_node_t *new_next = walk->next->next;
        sl_destroy_node(walk->next);
        walk->next = new_next;
    }
}

sl_node_t *sl_get_node(sl_list_t *list, int index)
{
    sl_node_t *walk = list->head;
    for (int i = 0; walk && i < index; ++i)
        walk = walk->next;
    return walk;
}

/* --- ENDOF: SINGLY LINKED LIST DEFINITIONS --- */
/* --------------------------------------------- */

/* --------------------------------------------- */
/* --- BEGIN: DOUBLY LINKED LIST DEFINITIONS --- */

dl_node_t *dl_create_node(void)
{
    dl_node_t *node = (dl_node_t *)calloc(1, sizeof(dl_node_t));
    if (!node) {
        fputs("rtb_list.h: Error: dl_create_node: calloc failed\n", stderr);
        exit(EXIT_FAILURE);
    }
    return node;
}

dl_node_t *dl_destroy_node(dl_node_t *node)
{
    if (!node) {
        fputs("rtb_list.h: Error: dl_destroy_node: Cannot destroy NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    free(node->val);
    free(node);
    return NULL;
}

dl_list_t *dl_create_list(void)
{
    dl_list_t *list = (dl_list_t *)calloc(1, sizeof(dl_list_t));
    if (!list) {
        fputs("rtb_list.h: Error: dl_create_list: calloc failed\n", stderr);
        exit(EXIT_FAILURE);
    }
    return list;
}

dl_list_t *dl_destroy_list(dl_list_t *list)
{
    while (!dl_is_empty(list)) {
        dl_remove_node(list, list->head);
    }
    return NULL;
}

int dl_is_empty(dl_list_t *list)
{
    if ((list->head && !list->tail)
        || (!list->head && list->tail))
    {
        fputs("rtb_list.h: Error: dl_is_empty: Invalid list initialization\n", stderr);
        exit(EXIT_FAILURE);
    }
    return !list->head && !list->tail;
}

void dl_append_node(dl_list_t *list, dl_node_t *node)
{

}

void dl_insert_node(dl_list_t *list, dl_node_t *node, int pos)
{

}

void dl_remove_node(dl_list_t *list, dl_node_t *node)
{

}

/* --- ENDOF: DOUBLY LINKED LIST DEFINITIONS --- */
/* --------------------------------------------- */

#endif // RTB_DEFINE
#endif // RTB_LIST_H_

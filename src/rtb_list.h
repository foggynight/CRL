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
 * File Version: 0.9.0
 * First Commit: 2020-12-16
 * Last Updated: 2020-12-27
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
 * @param list Pointer to a pointer to the target list */
void sl_destroy_list(sl_list_t **list);

/* sl_empty: Check if a singly linked list is empty.
 * @param list Pointer to the target list
 * @return Non-zero if the list is empty */
int sl_empty(sl_list_t *list);

/* sl_length: Get the number of nodes in a singly linked list.
 * @param list List to count
 * @return Number of nodes in the list */
int sl_length(sl_list_t *list);

/* sl_get: Get a node from a singly linked list using its index.
 * @param list  List of nodes
 * @param index Position of the node
 * @return If list contains index: node at index, else: NULL */
sl_node_t *sl_get(sl_list_t *list, int index);

/* sl_index: Get the index of a node in a singly linked list.
 * @param list List to search through
 * @param node Node to search for
 * @return If list contains node: index of node, else: -1 */
int sl_index(sl_list_t *list, sl_node_t *node);

/* sl_append: Append a node to a singly linked list.
 * @param list Pointer to the target list
 * @param node Pointer to the node to add */
void sl_append(sl_list_t *list, sl_node_t *node);

/* sl_insert: Insert a node in a singly linked list.
 * @param list  Pointer to the target list
 * @param node  Pointer to the node to add
 * @param index Position to insert the node */
void sl_insert(sl_list_t *list, sl_node_t *node, int index);

/* sl_remove: Remove a node from a singly linked list.
 * @param list Pointer to the target list
 * @param node Pointer to the node to remove
 * @param release If non-zero free val member */
void sl_remove(sl_list_t *list, sl_node_t *node, int release);

/* sl_replace: Replace a node in a singly linked list.
 * @param list  Pointer to the target list
 * @param node  Pointer to the node to add
 * @param index Position of node to replace */
void sl_replace(sl_list_t *list, sl_node_t *node, int index);

/* sl_push: Push a node onto the end of a singly linked list.
 * @param list List to push onto
 * @param node Node to push */
void sl_push(sl_list_t *list, sl_node_t *node);

/* sl_pop: Pop a node from the end of a singly linked list.
 * @param list List to pop from
 * @return Popped node */
sl_node_t *sl_pop(sl_list_t *list);

/* sl_enque: Enqueue a node onto the end of a singly linked list.
 * @param list List to enqueue to
 * @param node Node to enqueue */
void sl_enque(sl_list_t *list, sl_node_t *node);

/* sl_deque: Dequeue a node from the front of a singly linked list.
 * @param list List to dequeue from
 * @return Dequeued node */
sl_node_t *sl_deque(sl_list_t *list);

/* --- ENDOF: SINGLY LINKED LIST DECLARATIONS --- */
/* ---------------------------------------------- */

/* ---------------------------------------------- */
/* --- BEGIN: DOUBLY LINKED LIST DECLARATIONS --- */

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

void sl_destroy_list(sl_list_t **list)
{
    if (!list || !*list) {
        fputs("rtb_list.h: Error: sl_destroy_list: list is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    while (!sl_empty(*list))
        sl_remove(*list, (*list)->head, 1);
    free(*list);
    *list = NULL;
}

int sl_empty(sl_list_t *list)
{
    if (!list) {
        fputs("rtb_list.h: Error: sl_empty: list is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if ((list->head && !list->tail)
        || (!list->head && list->tail))
    {
        fputs("rtb_list.h: Error: sl_empty: invalid list initialization\n", stderr);
        exit(EXIT_FAILURE);
    }
    return !list->head && !list->tail;
}

int sl_length(sl_list_t *list)
{
    if (!list) {
        fputs("rtb_list.h: Error: sl_get: list is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    int count = 0;
    for (sl_node_t *walk = list->head; walk; walk = walk->next)
        ++count;
    return count;
}

sl_node_t *sl_get(sl_list_t *list, int index)
{
    if (!list) {
        fputs("rtb_list.h: Error: sl_get: list is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (index < 0) {
        fputs("rtb_list.h: Error: sl_get: invalid index\n", stderr);
        exit(EXIT_FAILURE);
    }
    sl_node_t *walk = list->head;
    for (int i = 0; walk && i < index; ++i)
        walk = walk->next;
    return walk;
}

int sl_index(sl_list_t *list, sl_node_t *node)
{
    if (!list) {
        fputs("rtb_list.h: Error: sl_index: list is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (!node) {
        fputs("rtb_list.h: Error: sl_index: node is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    sl_node_t *walk = list->head;
    for (int i = 0; walk; ++i) {
        if (walk == node)
            return i;
        walk = walk->next;
    }
    return -1;
}

void sl_append(sl_list_t *list, sl_node_t *node)
{
    if (!list) {
        fputs("rtb_list.h: Error: sl_append: list is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (!node) {
        fputs("rtb_list.h: Error: sl_append: node is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (sl_empty(list)) {
        list->head = list->tail = node;
    }
    else {
        list->tail->next = node;
        list->tail = node;
    }
}

void sl_insert(sl_list_t *list, sl_node_t *node, int index)
{
    if (!list) {
        fputs("rtb_list.h: Error: sl_insert: list is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (!node) {
        fputs("rtb_list.h: Error: sl_insert: node is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (index < 0) {
        fputs("rtb_list.h: Error: sl_insert: invalid index\n", stderr);
        exit(EXIT_FAILURE);
    }
    else if (sl_empty(list)) {
        list->head = list->tail = node;
    }
    else if (index == 0) {
        node->next = list->head;
        list->head = node;
    }
    else {
        int i = 0;
        sl_node_t *last = NULL, *walk = list->head;
        while (i < index && walk) {
            last = walk;
            walk = walk->next;
            ++i;
        }
        last->next = node;
        node->next = walk;
        if (!walk)
            list->tail = node;
    }
}

void sl_remove(sl_list_t *list, sl_node_t *node, int release)
{
    if (!list) {
        fputs("rtb_list.h: Error: sl_remove: list is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (!node) {
        fputs("rtb_list.h: Error: sl_remove: node is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (sl_empty(list)) {
        fputs("rtb_list.h: Error: sl_remove: list is empty\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (node == list->head) {
        sl_node_t *old_head = list->head;
        list->head = (list->head)->next;
        if (old_head == list->tail)
            list->tail = list->head;
        if (release)
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
        if (release)
            sl_destroy_node(old_tail);
    }
    else {
        sl_node_t *walk;
        for (walk = list->head;
             walk->next != node;
             walk = walk->next);
        sl_node_t *new_next = walk->next->next;
        if (release)
            sl_destroy_node(walk->next);
        walk->next = new_next;
    }
}

void sl_replace(sl_list_t *list, sl_node_t *node, int index)
{
    if (!list) {
        fputs("rtb_list.h: Error: sl_replace: list is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (!node) {
        fputs("rtb_list.h: Error: sl_replace: node is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (sl_empty(list)) {
        list->head = list->tail = node;
    }
    else {
        sl_insert(list, node, index);
        sl_remove(list, node->next, 1);
    }
}

void sl_push(sl_list_t *list, sl_node_t *node)
{
    if (!list) {
        fputs("rtb_list.h: Error: sl_push: list is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (!node) {
        fputs("rtb_list.h: Error: sl_push: node is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    sl_append(list, node);
}

sl_node_t *sl_pop(sl_list_t *list)
{
    if (!list) {
        fputs("rtb_list.h: Error: sl_pop: list is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    sl_node_t *node = list->tail;
    if (node)
        sl_remove(list, node, 0);
    return node;
}

void sl_enque(sl_list_t *list, sl_node_t *node)
{
    if (!list) {
        fputs("rtb_list.h: Error: sl_enque: list is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (!node) {
        fputs("rtb_list.h: Error: sl_enque: node is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    sl_insert(list, node, 0);
}

sl_node_t *sl_deque(sl_list_t *list)
{
    if (!list) {
        fputs("rtb_list.h: Error: sl_deque: list is NULL\n", stderr);
        exit(EXIT_FAILURE);
    }
    return sl_pop(list);
}

/* --- ENDOF: SINGLY LINKED LIST DEFINITIONS --- */
/* --------------------------------------------- */

/* --------------------------------------------- */
/* --- BEGIN: DOUBLY LINKED LIST DEFINITIONS --- */

/* --- ENDOF: DOUBLY LINKED LIST DEFINITIONS --- */
/* --------------------------------------------- */

#endif // RTB_DEFINE
#endif // RTB_LIST_H_

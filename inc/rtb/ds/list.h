/* list.h - v0.0.0 - Generic linked list
 *
 * Define the RTB_DEFINE macro before including this header in just one
 * compilation unit of your program.
 *
 * This file is part of the rtb library: http://foggynight.ca/git/rtb
 *
 * Copyright (C) 2020-2021 Robert Coffey
 * Released under the MIT license */

#ifndef RTB_DS_LIST_H_
#define RTB_DS_LIST_H_

#include "node.h"

/* sl_list_t: Singly linked list. */
typedef struct sl_list {
    sl_node_t *head; // Pointer to the head of the list
    sl_node_t *tail; // Pointer to the tail of the list
} sl_list_t;

/* sl_create_list: Create a singly linked list.
 * @return Pointer to the new list */
sl_list_t *sl_create_list(void);

/* sl_destroy_list: Destroy a singly linked list.
 * @param list Pointer to a pointer to the target list */
void sl_destroy_list(sl_list_t **list);

/* sl_empty_p: Predicate: Is a singly linked list is empty.
 * @param list Pointer to the target list
 * @return Non-zero if the list is empty */
int sl_empty_p(sl_list_t *list);

/* sl_node_c: Count: Get the number of nodes in a singly linked list.
 * @param list Pointer to the target list
 * @return Number of nodes in the list */
int sl_node_c(sl_list_t *list);

/* sl_get_node: Get a node using its index in a singly linked list.
 * @param list  Pointer to the target list
 * @param index Position of the target node
 * @return If list contains index: node at index, else: NULL */
sl_node_t *sl_get_node(sl_list_t *list, int index);

/* sl_get_index: Get the index of a node in a singly linked list.
 * @param list Pointer to the target list
 * @param node Pointer to the target node
 * @return If list contains node: index of node, else: -1 */
int sl_get_index(sl_list_t *list, sl_node_t *node);

/* sl_append: Append a node to a singly linked list.
 * @param list Pointer to the target list
 * @param node Pointer to the target node */
void sl_append(sl_list_t *list, sl_node_t *node);

/* sl_insert: Insert a node in a singly linked list.
 * @param list  Pointer to the target list
 * @param node  Pointer to the target node
 * @param index Position to insert the node */
void sl_insert(sl_list_t *list, sl_node_t *node, int index);

/* sl_remove: Remove a node from a singly linked list.
 * @param list    Pointer to the target list
 * @param node    Pointer to the target node
 * @param release If non-zero free val member */
void sl_remove(sl_list_t *list, sl_node_t *node, int release);

/* sl_remove_at: Remove a node from a singly linked list using its
 *     index.
 * @param list    Pointer to the target list
 * @param index   Position of the target node
 * @param release If non-zero free val member
 * @return Non-zero if node was removed */
int sl_remove_at(sl_list_t *list, int index, int release);

/* sl_replace: Replace a node in a singly linked list.
 * @param list Pointer to the target list
 * @param targ Pointer to the target node
 * @param node Pointer to the new node */
void sl_replace(sl_list_t *list, sl_node_t *targ, sl_node_t *node);

/* sl_replace_at: Replace a node in a singly linked list using its
 *     index.
 * @param list  Pointer to the target list
 * @param index Position of the target node
 * @param node  Pointer to the new node */
void sl_replace_at(sl_list_t *list, int index, sl_node_t *node);

#ifdef RTB_DEFINE

#include <stdlib.h>

#include "../log.h"

sl_list_t *sl_create_list(void)
{
    sl_list_t *list = (sl_list_t *)calloc(1, sizeof(sl_list_t));
    if (!list)
        rtb_elog("sl_create_list: calloc failed");
    return list;
}

void sl_destroy_list(sl_list_t **list)
{
    if (!list || !*list)
        rtb_elog("sl_destroy_list: list is NULL");
    while (!sl_empty_p(*list))
        sl_remove(*list, (*list)->head, 1);
    free(*list);
    *list = NULL;
}

int sl_empty_p(sl_list_t *list)
{
    if (!list)
        rtb_elog("sl_empty_p: list is NULL");
    if ((list->head && !list->tail)
            || (!list->head && list->tail))
        rtb_elog("sl_empty_p: invalid list initialization");
    return !list->head && !list->tail;
}

int sl_node_c(sl_list_t *list)
{
    if (!list)
        rtb_elog("sl_node_c: list is NULL");
    int count = 0;
    for (sl_node_t *walk = list->head; walk; walk = walk->next)
        ++count;
    return count;
}

sl_node_t *sl_get_node(sl_list_t *list, int index)
{
    if (!list)
        rtb_elog("sl_get_node: list is NULL");
    if (index < 0)
        rtb_elog("sl_get_node: invalid index");
    sl_node_t *walk = list->head;
    for (int i = 0; walk && i < index; ++i)
        walk = walk->next;
    return walk;
}

int sl_get_index(sl_list_t *list, sl_node_t *node)
{
    if (!list)
        rtb_elog("sl_get_index: list is NULL");
    if (!node)
        rtb_elog("sl_get_index: node is NULL");
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
    if (!list)
        rtb_elog("sl_append: list is NULL");
    if (!node)
        rtb_elog("sl_append: node is NULL");
    if (sl_empty_p(list)) {
        list->head = list->tail = node;
    }
    else {
        list->tail->next = node;
        list->tail = node;
    }
}

void sl_insert(sl_list_t *list, sl_node_t *node, int index)
{
    if (!list)
        rtb_elog("sl_insert: list is NULL");
    if (!node)
        rtb_elog("sl_insert: node is NULL");
    if (index < 0)
        rtb_elog("sl_insert: invalid index");
    if (sl_empty_p(list)) {
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
    if (!list)
        rtb_elog("sl_remove: list is NULL");
    if (!node)
        rtb_elog("sl_remove: node is NULL");
    if (sl_empty_p(list))
        rtb_elog("sl_remove: list is empty");
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

int sl_remove_at(sl_list_t *list, int index, int release)
{
    if (!list)
        rtb_elog("sl_remove_at: list is NULL");
    if (index < 0)
        rtb_elog("sl_remove_at: invalid inbex");
    if (sl_empty_p(list))
        rtb_elog("sl_remove_at: list is empty");
    int count = 0;
    sl_node_t *targ = list->head;
    while (targ && count < index)
        targ = targ->next;
    if (targ)
        sl_remove(list, targ, release);
    return targ ? 1 : 0;
}

void sl_replace(sl_list_t *list, sl_node_t *targ, sl_node_t *node)
{
    sl_replace_at(list, sl_get_index(list, targ), node);
}

void sl_replace_at(sl_list_t *list, int index, sl_node_t *node)
{
    if (!list)
        rtb_elog("sl_replace_at: list is NULL");
    if (!node)
        rtb_elog("sl_replace_at: node is NULL");
    if (sl_empty_p(list)) {
        list->head = list->tail = node;
    }
    else {
        sl_insert(list, node, index);
        sl_remove(list, node->next, 1);
    }
}

#endif // RTB_DEFINE
#endif // RTB_DS_LIST_H_

/* Version History
 * 0.0.0 - 2020-12-16 - First commit */

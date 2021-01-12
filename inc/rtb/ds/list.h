/**
 * list.h - v0.0.0 - Generic linked list types and associated functions
 *
 * Define the RTB_DEFINE macro before including this header in just one
 * compilation unit of your program.
 *
 * This file is part of the rtb library: http://foggynight.ca/git/rtb
 *
 * Copyright (C) 2020-2021 Robert Coffey Released under the MIT license
 **/

#ifndef RTB_DS_LIST_H_
#define RTB_DS_LIST_H_

#include "node.h"

/**
 * rtb_list1_t: Singly linked list type
 * @member head Pointer to the head of the list
 * @member tail Pointer to the tail of the list
 **/
typedef struct rtb_list1 {
    rtb_node1_t *head;
    rtb_node1_t *tail;
} rtb_list1_t;

/**
 * rtb_list1_create: Create a singly linked list
 * @return Pointer to the new list
 * @note All list members are initialized to zero
 **/
rtb_list1_t *rtb_list1_create(void);

/**
 * rtb_list1_destroy: Destroy a singly linked list
 * @param list Pointer to the target list
 * @note list must not be NULL
 * @note Side effects:
 *  - Destroys all nodes contained in the list
 **/
void rtb_list1_destroy(rtb_list1_t *list);

/**
 * rtb_list1_empty_p: Empty list predicate
 * @param list Pointer to the target list
 * @return Non-zero if the list is empty
 * @note list must not be NULL
 **/
int rtb_list1_empty_p(rtb_list1_t *list);

/**
 * rtb_list1_node_c: Count the number of nodes in a list
 * @param list Pointer to the target list
 * @return Number of nodes in the list
 * @note list must not be NULL
 **/
int rtb_list1_node_c(rtb_list1_t *list);

/**
 * rtb_list1_get_node: Get a node using its index in a singly linked
 *     list
 * @param list  Pointer to the target list
 * @param index Position of the target node
 * @return If list contains index: node at index, else: NULL
 * @note list must not be NULL
 * @note index must be greater than zero
 **/
rtb_node1_t *rtb_list1_get_node(rtb_list1_t *list, int index);

/**
 * rtb_list1_get_index: Get the index of a node in a singly linked list
 * @param list Pointer to the target list
 * @param node Pointer to the target node
 * @return If list contains node: index of node, else: -1
 **/
int rtb_list1_get_index(rtb_list1_t *list, rtb_node1_t *node);

/**
 * rtb_list1_insert_before: Insert a node in a singly linked list before
 *     another node in the list
 * @param list Pointer to the target list
 * @param node Pointer to the target node
 * @param next Pointer to the node to insert before
 * @note If next is NULL, inserts at the end of the list
 **/
void rtb_list1_insert_before(rtb_list1_t *list, rtb_node1_t *node, rtb_node1_t *next);

/**
 * rtb_list1_insert_after: Insert a node in a singly linked list after
 *     another node in the list
 * @param list Pointer to the target list
 * @param node Pointer to the target node
 * @param prev Pointer to the node to insert after
 * @note If prev is NULL, inserts at the beginning of the list
 **/
void rtb_list1_insert_after(rtb_list1_t *list, rtb_node1_t *node, rtb_node1_t *prev);

/**
 * rtb_list1_insert_at: Insert a node in a singly linked list using its
 *     index
 * @param list  Pointer to the target list
 * @param node  Pointer to the target node
 * @param index Position to insert the node
 **/
void rtb_list1_insert_at(rtb_list1_t *list, rtb_node1_t *node, int index);

/**
 * rtb_list1_remove: Remove a node from a singly linked list
 * @param list    Pointer to the target list
 * @param node    Pointer to the target node
 * @param release If non-zero: free val member
 **/
void rtb_list1_remove(rtb_list1_t *list, rtb_node1_t *node, int release);

/**
 * rtb_list1_remove_at: Remove a node from a singly linked list using
 *     its index
 * @param list    Pointer to the target list
 * @param index   Position of the target node
 * @param release If non-zero: free val member
 **/
void rtb_list1_remove_at(rtb_list1_t *list, int index, int release);

/**
 * rtb_list1_replace: Replace a node in a singly linked list
 * @param list     Pointer to the target list
 * @param node     Pointer to the target node
 * @param new_node Pointer to the new node
 **/
void rtb_list1_replace(rtb_list1_t *list, rtb_node1_t *node, rtb_node1_t *new_node);

/**
 * rtb_list1_replace_at: Replace a node in a singly linked list using
 *     its index
 * @param list     Pointer to the target list
 * @param index    Position of the target node
 * @param new_node Pointer to the new node
 **/
void rtb_list1_replace_at(rtb_list1_t *list, int index, rtb_node1_t *new_node);

#ifdef RTB_DEFINE

#include <stdlib.h>

#include "../log.h"

/* Implementations in this header rely on rtb_elog calling exit. */
#ifdef RTB_NO_EXIT
#undef RTB_NO_EXIT

rtb_list1_t *rtb_list1_create(void)
{
    rtb_list1_t *list = (rtb_list1_t *)calloc(1, sizeof(rtb_list1_t));
    if (!list)
        rtb_elog("rtb_list1_create: calloc failed");

    return list;
}

void rtb_list1_destroy(rtb_list1_t *list)
{
    if (!list)
        rtb_elog("rtb_list1_destroy: list is NULL");

    while (!rtb_list1_empty_p(list))
        rtb_list1_remove(list, list->head, 1);
    free(list);

    return NULL;
}

int rtb_list1_empty_p(rtb_list1_t *list)
{
    if (!list)
        rtb_elog("rtb_list1_empty_p: list is NULL");

    return !list->head;
}

int rtb_list1_node_c(rtb_list1_t *list)
{
    if (!list)
        rtb_elog("rtb_list1_node_c: list is NULL");

    int count = 0;
    for (rtb_node1_t *walk = list->head; walk; walk = walk->next)
        ++count;

    return count;
}

rtb_node1_t *rtb_list1_get_node(rtb_list1_t *list, int index)
{
    if (!list)
        rtb_elog("rtb_list1_get_node: list is NULL");
    if (index < 0)
        rtb_elog("rtb_list1_get_node: Invalid index");

    rtb_node1_t *walk = list->head;
    for (int i = 0; walk && i < index; ++i)
        walk = walk->next;

    return walk;
}

int rtb_list1_get_index(rtb_list1_t *list, rtb_node1_t *node)
{
    if (!list)
        rtb_elog("rtb_list1_get_index: list is NULL");
    if (!node)
        rtb_elog("rtb_list1_get_index: node is NULL");

    rtb_node1_t *walk = list->head;
    for (int i = 0; walk; ++i) {
        if (walk == node)
            return i;
        walk = walk->next;
    }

    return -1;
}

void rtb_list1_insert_before(rtb_list1_t *list, rtb_node1_t *node, rtb_node1_t *next)
{
    if (!list)
        rtb_elog("rtb_list1_insert_before: list is NULL");
    if (!node)
        rtb_elog("rtb_list1_insert_before: node is NULL");

    rtb_node1_t *walk = list->head;
    if (!walk) { // List is empty
        if (next)
            rtb_elog("rtb_list1_insert_before: list does not contain next");
        list->head = list->tail = node;
    }
    else if (!next) { // Insert at the end of the list
        list->tail->next = node;
        list->tail = node;
    }
    else if (next == list->head) { // Insert at the start of the list
        node->next = list->head;
        list->head = node;
    }
    else { // Insert within list body
        while (walk && walk->next != next)
            walk = walk->next;
        if (!walk)
            rtb_elog("rtb_list1_insert_before: list does not contain next");
        node->next = walk->next;
        walk->next = node;
    }
}

void rtb_list1_insert_after(rtb_list1_t *list, rtb_node1_t *node, rtb_node1_t *prev)
{
    if (!list)
        rtb_elog("rtb_list1_insert_after: list is NULL");
    if (!node)
        rtb_elog("rtb_list1_insert_after: node is NULL");

    if (!prev) { // Insert at the start of the list
        node->next = list->head;
        list->head = node;
    }
    else { // Insert in the body or at the end of the list
        node->next = prev->next;
        prev->next = node;
    }

    if (prev == list->tail)
        list->tail = node;
}

void rtb_list1_insert_at(rtb_list1_t *list, rtb_node1_t *node, int index)
{
    if (!list)
        rtb_elog("rtb_list1_insert_at: list is NULL");
    if (!node)
        rtb_elog("rtb_list1_insert_at: node is NULL");
    if (index < 0)
        rtb_elog("rtb_list1_insert_at: Invalid index");

    if (rtb_list1_empty_p(list)) {
        list->head = list->tail = node;
    }
    else if (index == 0) { // Insert at the start of the list
        node->next = list->head;
        list->head = node;
    }
    else { // Insert in the body or at the end of the list
        int i = 0;
        rtb_node1_t *walk = list->head, last = NULL;
        while (walk && i < index) {
            last = walk;
            walk = walk->next;
            ++i;
        }
        if (last)
            last->next = node;
        node->next = walk;
        if (!walk)
            list->tail = node;
    }
}

void rtb_list1_remove(rtb_list1_t *list, rtb_node1_t *node, int release)
{
    if (!list)
        rtb_elog("rtb_list1_remove: list is NULL");
    if (!node)
        rtb_elog("rtb_list1_remove: node is NULL");
    if (rtb_list1_empty_p(list))
        rtb_elog("rtb_list1_remove: list is empty");

    if (node == list->head) {
        rtb_node1_t *old_head = list->head;
        list->head = (list->head)->next;
        if (old_head == list->tail)
            list->tail = list->head;
        if (release)
            rtb_node1_destroy(old_head);
    }
    else if (node == list->tail) {
        rtb_node1_t *old_tail = list->tail;
        rtb_node1_t *walk;
        for (walk = list->head;
             walk->next != list->tail;
             walk = walk->next);
        list->tail = walk;
        list->tail->next = NULL;
        if (release)
            rtb_node1_destroy(old_tail);
    }
    else { // Insert in the body of the list
        rtb_node1_t *walk;
        for (walk = list->head;
             walk->next != node;
             walk = walk->next);
        rtb_node1_t *new_next = walk->next->next;
        if (release)
            rtb_node1_destroy(walk->next);
        walk->next = new_next;
    }
}

void rtb_list1_remove_at(rtb_list1_t *list, int index, int release)
{
    if (!list)
        rtb_elog("rtb_list1_remove_at: list is NULL");
    if (rtb_list1_empty_p(list))
        rtb_elog("rtb_list1_remove_at: list is empty");
    if (index < 0 || index >= rtb_list1_node_c(list))
        rtb_elog("rtb_list1_remove_at: Invalid index");

    int count = 0;
    rtb_node1_t *walk = list->head;
    while (walk && count < index) {
        walk = walk->next;
        ++count;
    }

    if (!walk)
        rtb_elog("rtb_list1_remove_at: walk is NULL");

    rtb_list1_remove(list, walk, release);
}

void rtb_list1_replace(rtb_list1_t *list, rtb_node1_t *targ, rtb_node1_t *node)
{
    if (!list)
        rtb_elog("rtb_list1_replace: list is NULL");
    if (!targ)
        rtb_elog("rtb_list1_replace: targ is NULL");
    if (!node)
        rtb_elog("rtb_list1_replace: node is NULL");
    if (rtb_list1_empty_p(list))
        rtb_elog("rtb_list1_replace: list is empty");

    if (targ == list->head) { // Replace list head
        rtb_list1_remove(list, list->head, 1);
        rtb_list1_insert_after(list, node, NULL);
    }
    else if (targ == list->tail) { // Replace list tail
        rtb_list1_remove(list, list->tail, 1);
        rtb_list1_insert_before(list, node, NULL);
    }
    else { // Replace node in list body
        rtb_node1_t *walk = list->head;
        while (walk && walk->next != targ)
            walk = walk->next;

        if (!walk)
            rtb_elog("rtb_list1_replace: walk is NULL");

        rtb_list1_remove(list, walk->next, 1);
        rtb_list1_insert_after(list, walk, node);
    }
}

void rtb_list1_replace_at(rtb_list1_t *list, int index, rtb_node1_t *node)
{
    if (!list)
        rtb_elog("rtb_list1_replace_at: list is NULL");
    if (!node)
        rtb_elog("rtb_list1_replace_at: node is NULL");

    if (rtb_list1_empty_p(list)) {
        list->head = list->tail = node;
    }
    else {
        rtb_list1_insert_at(list, node, index);
        rtb_list1_remove(list, node->next, 1);
    }
}

#endif // RTB_DEFINE
#endif // RTB_DS_LIST_H_

/**
 * Version History
 * 0.0.0 - 2020-12-16 - First commit
 **/

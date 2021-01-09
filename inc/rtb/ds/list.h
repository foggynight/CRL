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
 * @param list Double pointer to the target list
 * @note list and *list must not be NULL
 * @note Side effects:
 *  - Call: rtb_node1_destroy on all list nodes
 *  - Assign: *list = NULL
 **/
void rtb_list1_destroy(rtb_list1_t **list);

/**
 * rtb_list1_empty_p: Empty list predicate
 * @param list Pointer to the target list
 * @return Non-zero if the list is empty
 **/
int rtb_list1_empty_p(rtb_list1_t *list);

/**
 * rtb_list1_node_c: Count the number of nodes in a list
 * @param list Pointer to the target list
 * @return Number of nodes in the list
 **/
int rtb_list1_node_c(rtb_list1_t *list);

/**
 * rtb_list1_get_node: Get a node using its index in a singly linked
 *     list
 * @param list  Pointer to the target list
 * @param index Position of the target node
 * @return If list contains index: node at index, else: NULL
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
 **/
void rtb_list1_insert_before(rtb_list1_t *list, rtb_node1_t *node, rtb_node1_t *next);

/**
 * rtb_list1_insert_after: Insert a node in a singly linked list after
 *     another node in the list
 * @param list Pointer to the target list
 * @param node Pointer to the target node
 * @param prev Pointer to the node to insert after
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

rtb_list1_t *rtb_list1_create(void)
{
    rtb_list1_t *list = (rtb_list1_t *)calloc(1, sizeof(rtb_list1_t));
    if (!list)
        rtb_elog("rtb_list1_create: calloc failed");

    return list;
}

void rtb_list1_destroy(rtb_list1_t **list)
{
    if (!list)
        rtb_elog("rtb_list1_destroy: list is NULL");
    if (!*list)
        rtb_elog("rtb_list1_destroy: *list is NULL");

    while (!rtb_list1_empty_p(*list))
        rtb_list1_remove(*list, (*list)->head, 1);

    free(*list);
    *list = NULL;
}

int rtb_list1_empty_p(rtb_list1_t *list)
{
    if (!list)
        rtb_elog("rtb_list1_empty_p: list is NULL");
    if ((list->head && !list->tail)
     || (!list->head && list->tail))
        rtb_elog("rtb_list1_empty_p: invalid list initialization");

    return !list->head && !list->tail;
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
        rtb_elog("rtb_list1_get_node: invalid index");

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

void rtb_list1_insert_at(rtb_list1_t *list, rtb_node1_t *node, int index)
{
    if (!list)
        rtb_elog("rtb_list1_insert_at: list is NULL");
    if (!node)
        rtb_elog("rtb_list1_insert_at: node is NULL");
    if (index < 0)
        rtb_elog("rtb_list1_insert_at: invalid index");

    if (rtb_list1_empty_p(list)) {
        list->head = list->tail = node;
    }
    else if (index == 0) {
        node->next = list->head;
        list->head = node;
    }
    else {
        int i = 0;
        rtb_node1_t *last = NULL, *walk = list->head;
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
    else {
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

int rtb_list1_remove_at(rtb_list1_t *list, int index, int release)
{
    if (!list)
        rtb_elog("rtb_list1_remove_at: list is NULL");
    if (index < 0)
        rtb_elog("rtb_list1_remove_at: invalid inbex");
    if (rtb_list1_empty_p(list))
        rtb_elog("rtb_list1_remove_at: list is empty");

    int count = 0;
    rtb_node1_t *targ = list->head;
    while (targ && count < index) {
        targ = targ->next;
        ++count;
    }

    if (targ)
        rtb_list1_remove(list, targ, release);

    return targ ? 1 : 0;
}

void rtb_list1_replace(rtb_list1_t *list, rtb_node1_t *targ, rtb_node1_t *node)
{
    rtb_list1_replace_at(list, rtb_list1_get_index(list, targ), node);
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

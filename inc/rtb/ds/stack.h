/**
 * stack.h - v0.0.0 - Generic stack
 *
 * Define the RTB_DEFINE macro before including this header in just one
 * compilation unit of your program.
 *
 * This file is part of the rtb library: http://foggynight.ca/git/rtb
 *
 * Copyright (C) 2020-2021 Robert Coffey
 * Released under the MIT license
 **/

#ifndef RTB_DS_STACK_H_
#define RTB_DS_STACK_H_

#include "list.h"

/**
 * sl_push: Push a node onto the end of a singly linked list.
 * @param list Pointer to the target list
 * @param node Pointer to the target node
 **/
void sl_push(sl_list_t *list, sl_node_t *node);

/**
 * sl_pop: Pop a node from the end of a singly linked list.
 * @param list Pointer to the target list
 * @return Pointer to the popped node
 **/
sl_node_t *sl_pop(sl_list_t *list);

#ifdef RTB_DEFINE

#include "../log.h"

void sl_push(sl_list_t *list, sl_node_t *node)
{
    if (!list)
        rtb_elog("sl_push: list is NULL");
    if (!node)
        rtb_elog("sl_push: node is NULL");
    sl_append(list, node);
}

sl_node_t *sl_pop(sl_list_t *list)
{
    if (!list)
        rtb_elog("sl_pop: list is NULL");
    sl_node_t *node = list->tail;
    if (node)
        sl_remove(list, node, 0);
    return node;
}

#endif // RTB_DEFINE
#endif // RTB_DS_STACK_H_

/**
 * Version History
 * 0.0.0 - 2021-01-01 - First commit
 **/

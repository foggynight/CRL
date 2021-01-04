/**
 * queue.h - v0.0.0 - Generic queue
 *
 * Define the RTB_DEFINE macro before including this header in just one
 * compilation unit of your program.
 *
 * This file is part of the rtb library: http://foggynight.ca/git/rtb
 *
 * Copyright (C) 2020-2021 Robert Coffey
 * Released under the MIT license
 */

#ifndef RTB_DS_QUEUE_H_
#define RTB_DS_QUEUE_H_

#include "list.h"

/**
 * sl_enque: Enqueue a node onto the end of a singly linked list.
 * @param list Pointer to the target list
 * @param node Pointer to target node
 */
void sl_enque(sl_list_t *list, sl_node_t *node);

/**
 * sl_deque: Dequeue a node from the front of a singly linked list.
 * @param list Pointer to the target list
 * @return Pointer to the dequeued node
 */
sl_node_t *sl_deque(sl_list_t *list);

#ifdef RTB_DEFINE

#include "../log.h"

void sl_enque(sl_list_t *list, sl_node_t *node)
{
    if (!list)
        rtb_elog("sl_enque: list is NULL");
    if (!node)
        rtb_elog("sl_enque: node is NULL");
    sl_insert(list, node, 0);
}

sl_node_t *sl_deque(sl_list_t *list)
{
    if (!list)
        rtb_elog("sl_deque: list is NULL");
    return sl_pop(list);
}

#endif // RTB_DEFINE
#endif // RTB_DS_QUEUE_H_

/**
 * Version History
 * 0.0.0 - 2021-01-01 - First commit
 */

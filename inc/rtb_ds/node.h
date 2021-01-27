/**
 * node.h - v0.0.0 - Generic node types and associated functions
 *
 * Define the RTB_DEFINE macro before including this header in just one
 * compilation unit of your program.
 *
 * This file is part of the rtb library: http://foggynight.ca/git/rtb
 *
 * Copyright (C) 2020-2021 Robert Coffey
 * Released under the MIT license
 **/

#ifndef RTB_DS_NODE_H_
#define RTB_DS_NODE_H_

/**
 * rtb_node1_t: Generic singly linked node
 * @member val  Pointer to the node value
 * @member next Pointer to the next node
 **/
typedef struct rtb_node1 {
    void *val;
    struct rtb_node1 *next;
} rtb_node1_t;

/**
 * rtb_node1_create: Create a singly linked node
 * @return Pointer to the new node
 * @note All node members are initialized to zero
 **/
rtb_node1_t *rtb_node1_create(void);

/**
 * rtb_node1_destroy: Destroy a singly linked node
 * @param node Pointer to the target node
 * @return Always NULL
 * @note node must not be NULL
 * @note node->val will be freed if not-NULL
 **/
rtb_node1_t *rtb_node1_destroy(rtb_node1_t *node);

#ifdef RTB_DEFINE

#include <stdlib.h>

#include "../rtb_log.h"

rtb_node1_t *rtb_node1_create(void)
{
    rtb_node1_t *node = (rtb_node1_t *)calloc(1, sizeof(rtb_node1_t));
    if (!node)
        rtb_elog("rtb_node1_create: calloc failed");

    return node;
}

rtb_node1_t *rtb_node1_destroy(rtb_node1_t *node)
{
    if (!node)
        rtb_elog("rtb_node1_destroy: node is NULL");

    if (node->val)
        free(node->val);
    free(node);

    return NULL;
}

#endif // RTB_DEFINE
#endif // RTB_DS_NODE_H_

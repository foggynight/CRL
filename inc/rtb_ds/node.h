/* node.h - v0.0.0 - Generic node
 *
 * Define the RTB_DEFINE macro before including this header in just one
 * compilation unit of your program.
 *
 * This file is part of the rtb library: http://foggynight.ca/git/rtb
 *
 * Copyright (C) 2020-2021 Robert Coffey
 * Released under the MIT license */

#ifndef RTB_DS_NODE_H_
#define RTB_DS_NODE_H_

/* sl_node_t: Singly linked node. */
typedef struct sl_node {
    void *val;            // Pointer to the node value
    struct sl_node *next; // Pointer to the next node
} sl_node_t;

/* sl_create_node: Create a singly linked node.
 * @return Pointer to the new node */
sl_node_t *sl_create_node(void);

/* sl_destroy_node: Destroy a singly linked node.
 * @param node Pointer to the target node
 * @return Always NULL */
sl_node_t *sl_destroy_node(sl_node_t *node);

#ifdef RTB_DEFINE

#include <stdlib.h>

#include "../rtb_log.h"

sl_node_t *sl_create_node(void)
{
    sl_node_t *node = (sl_node_t *)calloc(1, sizeof(sl_node_t));
    if (!node)
        rtb_elog("sl_create_node: calloc failed");
    return node;
}

sl_node_t *sl_destroy_node(sl_node_t *node)
{
    if (!node)
        rtb_elog("sl_destroy_node: node is NULL");
    if (node->val)
        free(node->val);
    free(node);
    return NULL;
}

#endif // RTB_DEFINE
#endif // RTB_DS_NODE_H_

/* Version History
 * 0.0.0 - 2021-01-01 - First commit */

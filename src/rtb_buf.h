/* --- rtb_buf.h ---
 *
 * Generic variable sized buffer.
 *
 * File Version: 0.1.0
 * First Commit: 2020-12-28
 * Last Updated: 2020-12-28
 *
 * Copyright (C) 2020 Robert Coffey
 * Released under the MIT license */

#ifndef RTB_BUF_H_
#define RTB_BUF_H_

#include <stdlib.h>

#include "rtb_log.h"

typedef struct rtb_buf {
    size_t last; // Index of last element
    size_t size; // Size of the buffer
    void **data; // Data buffer
} rtb_buf_t;

/* rtb_buf: Create a buffer
 * @param size Initial size of the buffer */
rtb_buf_t *rtb_buf(size_t size);

/* rtb_buf_destroy: Destroy a buffer. */

/* rtb_buf_get: Get an element in the buffer */

/* rtb_buf_set: Set an element in the buffer */

/* rtb_buf_push: Push an element to the back of the buffer */

/* rtb_buf_pop: Pop an element from the back of the buffer */

#ifdef RTB_DEFINE

rtb_buf_t *rtb_buf(size_t size)
{
    rtb_buf_t *buf = (rtb_buf_t *)malloc(sizeof(rtb_buf_t));
    if (!buf)
        rtb_elog("rtb_buf: malloc failed");
    buf->last = 0;
    buf->size = size;
    buf->data = (void **)calloc(size, sizeof(void*));
    if (!buf->data)
        rtb_elog("rtb_buf: calloc failed");
    return buf;
}

/* rtb_buf_resize: Resize the data buffer */

#endif // RTB_DEFINE
#endif // RTB_BUF_H_

/* buffer.h - v0.0.0 - Generic buffer
 *
 * Define the RTB_DEFINE macro before including this header in just one
 * compilation unit of your program.
 *
 * This file is part of the rtb library: http://foggynight.ca/git/rtb
 *
 * Copyright (C) 2020-2021 Robert Coffey
 * Released under the MIT license */

#ifndef RTB_DS_BUFFER_H_
#define RTB_DS_BUFFER_H_

#include <stdlib.h>

#include "rtb_log.h"

typedef struct rtb_buf {
    size_t last; // Index of last element
    size_t size; // Size of the buffer
    void **data; // Data buffer
} rtb_buf_t;

/* rtb_buf: Create a buffer
 * @param size Initial size of the buffer
 * @return New buffer */
rtb_buf_t *rtb_buf(size_t size);

/* rtb_buf_destroy: Destroy a buffer
 * @param buf Target buffer
 * @return Always NULL */
rtb_buf_t *rtb_buf_destroy(rtb_buf_t *buf);

/* rtb_buf_get: Get an element in the buffer */

/* rtb_buf_set: Set an element in the buffer */

/* rtb_buf_push: Push an element to the back of the buffer */

/* rtb_buf_pop: Pop an element from the back of the buffer */

#ifdef RTB_DEFINE

#include "rtb_log.h"

rtb_buf_t *rtb_buf(size_t size)
{
    if (size < 0)
        rtb_elog("rtb_buf: invalid size");
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

rtb_buf_t *rtb_buf_destroy(rtb_buf_t *buf)
{
    if
    return NULL;
}

/* rtb_buf_resize: Resize the data buffer */

#endif // RTB_DEFINE
#endif // RTB_DS_BUFFER_H_

/* Version History
 * 0.0.0 - 2020-12-28 - First commit */

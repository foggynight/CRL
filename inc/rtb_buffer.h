/**
 * rtb_buffer.h - v0.0.0 - Variable sized generic buffer
 *
 * This file is part of the rtb library.
 *
 * Copyright (C) 2021 Robert Coffey
 * Released under the GPLv2 license
 **/

#ifndef RTB__BUFFER_H
#define RTB__BUFFER_H

#include <stddef.h>

typedef struct rtb_buffer {
	void **data;	// Data contained within the buffer
	size_t len;	// Length of the buffer -- Number of blocks allocated in data
	size_t end;	// Index after the last element in data -- Zero implies data is empty
} rtb_buffer_t;

rtb_buffer_t *rtb_buffer_init(size_t initial_len);
void rtb_buffer_destroy(rtb_buffer_t *buffer);
int rtb_buffer_empty(rtb_buffer_t *buffer);
int rtb_buffer_resize(rtb_buffer_t *buffer, size_t new_size);
int rtb_buffer_push(rtb_buffer_t *buffer, void *element);
void *rtb_buffer_pop(rtb_buffer_t *buffer);
void *rtb_buffer_at(rtb_buffer_t *buffer, size_t index);
int rtb_buffer_set(rtb_buffer_t *buffer, size_t index, void *value);

#endif	// RTB__BUFFER_H

#ifdef RTB_DEFINE

#include <stdlib.h>

#define GROWTH_FACTOR 2	// Buffer length is multiplied by GROWTH_FACTOR on growth

rtb_buffer_t *rtb_buffer_init(size_t initial_len)
{
	rtb_buffer_t *buffer = malloc(sizeof buffer);
	if (!buffer) return NULL;

	buffer->data = malloc(initial_len * sizeof(void *));
	if (!buffer->data) return NULL;

	buffer->len = initial_len;
	buffer->end = 0;

	return buffer;
}

void rtb_buffer_destroy(rtb_buffer_t *buffer)
{
	assert(buffer);

	free(buffer->data);
	free(buffer);
}

int rtb_buffer_empty(rtb_buffer_t *buffer)
{
	assert(buffer);

	return !buffer->end;
}

int rtb_buffer_resize(rtb_buffer_t *buffer, size_t new_len)
{
	assert(buffer);

	buffer->data = realloc(buffer->data, new_len * sizeof(void *));
	if (!buffer->data)
		return 0;

	buffer->len = new_len;
	return 1;
}

int rtb_buffer_push(rtb_buffer_t *buffer, void *element)
{
	assert(buffer);

	if (buffer->end == buffer->len) {
		size_t new_len = GROWTH_FACTOR * buffer->len;
		if (!rtb_buffer_resize(buffer, new_len))
			return 0;
	}

	buffer->data[buffer->end++] = element;
	return 1;
}

void *rtb_buffer_pop(rtb_buffer_t *buffer)
{
	assert(buffer);

	if (rtb_buffer_empty(buffer))
		return NULL;

	return buffer->data[(buffer->end--) - 1];
}

void *rtb_buffer_at(rtb_buffer_t *buffer, size_t index)
{
	assert(buffer);

	if (index >= buffer->end)
		return NULL;

	return buffer->data[index];
}

int rtb_buffer_set(rtb_buffer_t *buffer, size_t index, void *value)
{
	assert(buffer);

	if (index >= buffer->end)
		return 0;

	buffer->data[index] = value;
	return 1;
}

#endif	// RTB_DEFINE

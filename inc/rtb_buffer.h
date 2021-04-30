/**
 * rtb_buffer.h - v0.0.0 - Variable sized generic buffer
 *
 * This file is part of the rtb library.
 *
 * Copyright (C) 2021 Robert Coffey
 * Released under the GPLv2 license
 **/

#ifndef RTB_BUFFER_H
#define RTB_BUFFER_H

#include <stdlib.h>

#define GROWTH_FACTOR 2	// Buffer size is multiplied by GROWTH_FACTOR on resize

typedef struct rtb_buffer {
	void **data;	// Data contained within the buffer
	size_t size;	// Size of the buffer -- Number of blocks allocated in data
	size_t end;	// Index after the last element in data -- Zero implies data is empty
} rtb_buffer_t;

rtb_buffer_t *rtb_buffer_init(size_t initial_size);
void rtb_buffer_destroy(rtb_buffer_t *buffer);
int rtb_buffer_push(rtb_buffer_t *buffer, void *element);
void *rtb_buffer_pop(rtb_buffer_t *buffer);

#ifdef RTB_DEFINE

rtb_buffer_t *rtb_buffer_init(size_t initial_size)
{
	rtb_buffer_t *buffer = malloc(sizeof buffer);
	if (!buffer) return NULL;

	buffer->data = malloc(initial_size * sizeof(void *));
	if (!buffer->data) return NULL;

	buffer->size = initial_size;
	buffer->end = 0;

	return buffer;
}

void rtb_buffer_destroy(rtb_buffer_t *buffer)
{
	free(buffer->data);
	free(buffer);
}

int rtb_buffer_push(rtb_buffer_t *buffer, void *element)
{
	if (buffer->end == buffer->size) {
		size_t new_size = GROWTH_FACTOR * buffer->size;

		buffer->data = realloc(buffer->data, new_size * sizeof(void *));
		if (!buffer->data)
			return 0;

		buffer->size = new_size;
	}

	buffer->data[buffer->end++] = element;
	return 1;
}

void *rtb_buffer_pop(rtb_buffer_t *buffer)
{
	if (buffer->end < 1)
		return NULL;

	return buffer->data[(buffer->end--) - 1];
}

#endif // RTB_DEFINE
#endif // RTB_BUFFER_H

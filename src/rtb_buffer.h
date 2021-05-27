/**
 * rtb_buffer.h - v0.1.2 - Variable sized generic buffer type
 *
 * This file is part of the rtb library.
 *
 * Copyright (C) 2021 Robert Coffey
 * Released under the GPLv2 license
 **/

#ifndef RTB__BUFFER_H
#define RTB__BUFFER_H

#include <stddef.h>

/**
 * Variable sized generic buffer type. Implemented using a block of
 * void pointers.
 *
 * @member size	Number of pointers allocated in the data buffer
 * @member end	Index after the last element in the data buffer
 * @member data	Data buffer containing block of pointers
 **/
typedef struct rtb_buffer {
	size_t size;
	size_t end;
	void **data;
} rtb_buffer_t;

/**
 * Allocate an rtb_buffer_t and empty data buffer of size initial_size,
 * then set rtb_buffer_t members to their initial values.
 *
 * @param initial_size	Initial size of the data buffer
 *
 * @return Pointer to a new rtb_buffer_t or NULL on failure
 *
 * @note Must be destroyed using rtb_buffer_destroy
 **/
rtb_buffer_t *rtb_buffer_init(size_t initial_size);

/**
 * Destroy an rtb_buffer_t, freeing the data buffer and the rtb_buffer_t
 * itself.
 *
 * @param buffer	rtb_buffer_t to destroy
 **/
void rtb_buffer_destroy(rtb_buffer_t *buffer);

/**
 * Check if an rtb_buffer_t has an empty data buffer, represented by the
 * end member being equal to zero.
 *
 * @param buffer	rtb_buffer_t to check
 *
 * @return Non-zero if the data buffer is empty
 **/
int rtb_buffer_empty(rtb_buffer_t *buffer);

/**
 * Resize the data buffer of an rtb_buffer_t.
 *
 * @param buffer	rtb_buffer_t to resize
 * @param new_size	New size of the data buffer
 *
 * @return Non-zero on success
 *
 * @note new_size must be greater than current size of the data buffer
 * @note Calling this function on an rtb_buffer_t will invalidate any
 *	pointers to its data buffer.
 **/
int rtb_buffer_resize(rtb_buffer_t *buffer, size_t new_size);

/**
 * Push a pointer onto the end of the data buffer of an rtb_buffer_t,
 * incrementing its end member.
 *
 * @param buffer	rtb_buffer_t containing data buffer to push onto
 * @param element	Element to push onto the data buffer
 *
 * @return Non-zero on success
 *
 * @note Calling this function on an rtb_buffer_t may invalidate any
 *	pointers to its data buffer.
 **/
int rtb_buffer_push(rtb_buffer_t *buffer, void *element);

/**
 * Pop a pointer off the end of the data buffer of an rtb_buffer_t,
 * decrementing its end member.
 *
 * @param buffer	rtb_buffer_t containing data buffer to pop from
 *
 * @return Pointer popped off the data buffer
 *
 * @note The data buffer must not be empty, this can be checked for
 *	using rtb_buffer_empty
 **/
void *rtb_buffer_pop(rtb_buffer_t *buffer);

/**
 * Get the element at the given index in the data buffer of an
 * rtb_buffer_t.
 *
 * @param buffer	rtb_buffer_t containing data buffer to read from
 * @param index	Index in the data buffer to read from
 *
 * @return Pointer stored at index in the data buffer
 *
 * @note index must be less than the end member of the rtb_buffer_t
 **/
void *rtb_buffer_at(rtb_buffer_t *buffer, size_t index);

/**
 * Set the element at the given index in the data buffer of an
 * rtb_buffer_t.
 *
 * @param buffer	rtb_buffer_t containing data buffer to write to
 * @param index	Index in the data buffer to write to
 *
 * @return Pointer stored at index in the data buffer
 *
 * @note index must be less than the end member of the rtb_buffer_t
 **/
void rtb_buffer_set(rtb_buffer_t *buffer, size_t index, void *value);

#endif	// RTB__BUFFER_H

#ifdef RTB_DEFINE
#undef RTB_DEFINE

#include <assert.h>
#include <stdlib.h>

// The size of the data buffer of an rtb_buffer_t is multiplied by
// RTB__GROWTH_FACTOR when pushing onto an rtb_buffer_t at max capacity.
#define RTB__GROWTH_FACTOR 2

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
	assert(buffer);

	free(buffer->data);
	free(buffer);
}

int rtb_buffer_empty(rtb_buffer_t *buffer)
{
	assert(buffer);

	return !buffer->end;
}

int rtb_buffer_resize(rtb_buffer_t *buffer, size_t new_size)
{
	assert(buffer);
	assert(new_size > buffer->size);

	buffer->data = realloc(buffer->data, new_size * sizeof(void *));
	if (!buffer->data)
		return 0;

	buffer->size = new_size;
	return 1;
}

int rtb_buffer_push(rtb_buffer_t *buffer, void *element)
{
	assert(buffer);

	if (buffer->end == buffer->size) {
		size_t new_size = buffer->size ? buffer->size * RTB__GROWTH_FACTOR : 1;
		if (!rtb_buffer_resize(buffer, new_size))
			return 0;
	}

	buffer->data[buffer->end++] = element;
	return 1;
}

void *rtb_buffer_pop(rtb_buffer_t *buffer)
{
	assert(buffer);
	assert(!rtb_buffer_empty(buffer));

	return buffer->data[--buffer->end];
}

void *rtb_buffer_at(rtb_buffer_t *buffer, size_t index)
{
	assert(buffer);
	assert(index < buffer->end);

	return buffer->data[index];
}

void rtb_buffer_set(rtb_buffer_t *buffer, size_t index, void *value)
{
	assert(buffer);
	assert(index < buffer->end);

	buffer->data[index] = value;
}

#endif	// RTB_DEFINE

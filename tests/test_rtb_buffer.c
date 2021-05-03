// Copyright (C) 2021 Robert Coffey
// Released under the GPLv2 license

#include <assert.h>
#include <stdio.h>

#define RTB_DEFINE
#include "../inc/rtb_buffer.h"

void test_init_destroy(size_t initial_len);
void test_empty(size_t initial_len);

int main(void)
{
	test_init_destroy(0);
	test_init_destroy(1);
	test_init_destroy(64);

	test_empty(0);
	test_empty(1);
	test_empty(64);

	printf("test_rtb_buffer.c: All tests passed\n");
}

void test_init_destroy(size_t initial_len)
{
	rtb_buffer_t *buffer = NULL;
	buffer = rtb_buffer_init(initial_len);

	assert(buffer != NULL);
	assert(buffer->len == initial_len);
	assert(buffer->end == 0);

	rtb_buffer_destroy(buffer);
}

void test_empty(size_t initial_len)
{
	rtb_buffer_t *buffer = rtb_buffer_init(initial_len);

	assert(rtb_buffer_empty(buffer));

	rtb_buffer_push(buffer, (void *)0);
	assert(!rtb_buffer_empty(buffer));

	rtb_buffer_push(buffer, (void *)0);
	assert(!rtb_buffer_empty(buffer));

	rtb_buffer_destroy(buffer);
}

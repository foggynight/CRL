// Copyright (C) 2021 Robert Coffey
// Released under the GPLv2 license

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define RTB_DEFINE
#include "../inc/rtb_buffer.h"

void test_init_destroy(size_t initial_len);
void test_empty(size_t initial_len);
void test_resize(size_t initial_len, size_t new_len);
void test_push_pop(size_t initial_len, size_t value_count, void **values);
void test_at_set(void);

int main(void)
{
	test_init_destroy(0);
	test_init_destroy(1);
	test_init_destroy(64);

	test_empty(0);
	test_empty(1);
	test_empty(64);

	test_resize(0, 1);
	test_resize(1, 1);
	test_resize(1, 2);
	test_resize(2, 1);
	test_resize(2, 64);

	void *val_0 = malloc(sizeof(int));
	void *val_1 = malloc(sizeof(int));
	void *val_2 = malloc(sizeof(int));
	void *values[] = { val_0, val_1, val_2 };

	*(int *)val_0 = 0;
	*(int *)val_1 = 1;
	*(int *)val_2 = 2;
	test_push_pop(0, 3, values);

	*(int *)val_0 = 2;
	*(int *)val_1 = 1;
	*(int *)val_2 = 0;
	test_push_pop(8, 3, values);

	test_at_set();

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

	rtb_buffer_pop(buffer);
	assert(!rtb_buffer_empty(buffer));

	rtb_buffer_pop(buffer);
	assert(rtb_buffer_empty(buffer));

	rtb_buffer_destroy(buffer);
}

void test_resize(size_t initial_len, size_t new_len)
{
	rtb_buffer_t *buffer = rtb_buffer_init(initial_len);
	assert(buffer->len == initial_len);

	rtb_buffer_resize(buffer, new_len);
	assert(buffer->len == new_len);
}

void test_push_pop(size_t initial_len, size_t value_count, void **values)
{
	rtb_buffer_t *buffer = rtb_buffer_init(initial_len);

	for (int i = 0; i < value_count; ++i) {
		assert(buffer->end == i);
		rtb_buffer_push(buffer, values[i]);
		assert(buffer->end == i + 1);

		for (int j = 0; j < i; ++j) {
			assert(*(int *)buffer->data[j] == *(int *)values[j]);
		}
	}

	for (int i = value_count; i > 0; --i) {
		assert(buffer->end == i);
		int actual_value = *(int *)rtb_buffer_pop(buffer);
		assert(buffer->end == i - 1);

		int correct_value = *(int *)values[i - 1];
		assert(actual_value == correct_value);
	}
}

void test_at_set(void)
{
	const int value_count = 3;
	rtb_buffer_t *buffer = rtb_buffer_init(value_count);

	for (int i = 0; i < value_count; ++i) {
		rtb_buffer_push(buffer, NULL);
		assert(rtb_buffer_at(buffer, i) == NULL);
	}

	void *val_0 = malloc(sizeof(int));
	*(int *)val_0 = 0;

	void *val_1 = malloc(sizeof(int));
	*(int *)val_1 = 1;

	rtb_buffer_set(buffer, 0, val_0);
	rtb_buffer_set(buffer, value_count-1, val_1);

	for (int i = 0; i < value_count; ++i) {
		void *expected_value;
		if (i == 0)
			expected_value = val_0;
		else if (i == value_count-1)
			expected_value = val_1;
		else
			expected_value = NULL;
		assert(rtb_buffer_at(buffer, i) == expected_value);
	}
}

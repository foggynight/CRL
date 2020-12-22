# Copyright (C) 2020 Robert Coffey
# Released under the MIT license

CC=clang
CFLAGS=-I../src/ -Weverything

.PHONY: test
test:
	@+for t in $(wildcard test_*); do\
		$(CC) $(CFLAGS) $$t;\
		./a.out;\
		rm a.out;\
	done;\

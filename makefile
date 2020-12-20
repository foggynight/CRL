# Copyright (C) 2020 Robert Coffey
# Released under the MIT license

CC=clang
CFLAGS=-Weverything

.PHONY: test
test:
	@+for t in $(wildcard test/*); do\
		$(CC) $(CFLAGS) $$t;\
		./a.out;\
		rm a.out;\
	done;\

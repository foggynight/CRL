CC=clang
CFLAGS=-Weverything

SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:%.c=%.o)

.PHONY: test
test:
	@+for t in $(wildcard test/*); do\
		$(CC) $(CFLAGS) $$t;\
		./a.out;\
		rm a.out;\
	done;\

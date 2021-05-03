#!/bin/sh

# Copyright (C) 2021 Robert Coffey
# Released under the GPLv2 license

TESTS=test_rtb_buffer

for TEST in $TESTS; do
	gcc $TEST.c -o $TEST && ./$TEST && rm $TEST
done

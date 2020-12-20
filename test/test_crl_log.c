// Copyright (C) 2020 Robert Coffey
// Released under the GPLv2 license
// Target: crl_list.h v0.1.9

#include <stdio.h>

#define CRL_DEFINE
#include "../src/crl_log.h"

int main(void)
{
    log("This is a test");
    i_log("This is a test");
    w_log("This is a test");
    e_log("This is a test\n"
          "test_crl_log.c: All tests passed");
    return 0;
}

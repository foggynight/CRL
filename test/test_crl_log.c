/* --- test_crl_log.c ---
 *
 * Target: crl_log.h v0.2.x
 * First Commit: 2020-12-20
 * Last Updated: 2020-12-21
 *
 * Copyright (C) 2020 Robert Coffey
 * Released under the MIT license */

#include <stdio.h>

#define CRL_NO_EXIT
#include "crl_log.h"

int main(void)
{
    crl_log("This is a test");
    crl_ilog("This is a test");
    crl_wlog("This is a test");
    crl_elog("This is a test");

    crl_logf("%s\n", "This is a test");
    crl_ilogf("%s\n", "This is a test");
    crl_wlogf("%s\n", "This is a test");
    crl_elogf("%s\n", "This is a test");

    puts("test_crl_log.c: All tests passed");
    return 0;
}

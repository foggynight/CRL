/* --- test_rtb_log.c ---
 *
 * Target: rtb_log.h v0.1.0
 * First Commit: 2020-12-20
 * Last Updated: 2020-12-29
 *
 * Copyright (C) 2020 Robert Coffey
 * Released under the GPLv2 license */

#include <stdio.h>

#define RTB_NO_EXIT
#include "rtb_log.h"

int main(void)
{
    rtb_log("This is a test");
    rtb_ilog("This is a test");
    rtb_wlog("This is a test");
    rtb_elog("This is a test");

    rtb_logf("%s\n", "This is a test");
    rtb_ilogf("%s\n", "This is a test");
    rtb_wlogf("%s\n", "This is a test");
    rtb_elogf("%s\n", "This is a test");

    puts("test_rtb_log.c: All tests passed");
    return 0;
}

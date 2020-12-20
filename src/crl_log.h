/* --- crl_log.h ---
 *
 * Logging and error handling.
 *
 * File Version: 0.1.10
 * Last Updated: 2020-12-20
 *
 * This file is part of the crl library:
 * https://github.com/foggynight/crl
 *
 * Copyright (C) 2020 Robert Coffey
 * Released under the GPLv2 license */

#ifndef CRL_LOG_H_
#define CRL_LOG_H_

#include <stdio.h>
#include <stdlib.h>

#define CRL_LOG_INFO_ 0x1
#define CRL_LOG_WARN_ 0x2
#define CRL_LOG_ERR_  0x4

#define crl_log(X) do { log_(0, (X)); } while (0)
#define crl_ilog(X) do { log_(CRL_LOG_INFO_, (X)); } while (0)
#define crl_wlog(X) do { log_(CRL_LOG_WARN_, (X)); } while (0)
#define crl_elog(X) do { log_(CRL_LOG_ERR_, (X)); exit(EXIT_FAILURE); } while (0)

/** log_: Print a message to stderr with an optional preamble.
 * @param flags {int}: Flags indicating preamble
 * @param msg {const char *}: Message to print */
void log_(int flags, const char *msg);

#ifdef CRL_DEFINE

void log_(int flags, const char *msg)
{
    switch (flags) {
        case CRL_LOG_INFO_:
            fprintf(stderr, "Info: %s\n", msg);
            break;
        case CRL_LOG_WARN_:
            fprintf(stderr, "Warning: %s\n", msg);
            break;
        case CRL_LOG_ERR_:
            fprintf(stderr, "Error: %s\n", msg);
            break;
        default:
            fprintf(stderr, "%s\n", msg);
            break;
    }
}

#endif // CRL_DEFINE
#endif // CRL_LOG_H_

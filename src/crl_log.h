/* --- crl_log.h ---
 *
 * Logging and error handling.
 *
 * File Version: 0.1.8
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

#define LOG_INFO_ 0x1
#define LOG_WARN_ 0x2
#define LOG_ERR_  0x4

#define log(X)   { log_((X), 0); }
#define i_log(X) { log_((X), LOG_INFO_); }
#define w_log(X) { log_((X), LOG_WARN_); }
#define e_log(X) { log_((X), LOG_ERR_); \
                   exit(EXIT_FAILURE); }

/** log: Print a message to stderr with an optional preamble.
 * @param msg {const char *}: Message to print
 * @param flags {int}: Flags indicating preamble */
void log_(const char *msg, int flags);

#ifdef CRL_DEFINE

void log_(const char *msg, int flags)
{
    switch (flags) {
        case LOG_INFO_:
            fprintf(stderr, "Info: %s\n", msg);
            break;
        case LOG_WARN_:
            fprintf(stderr, "Warning: %s\n", msg);
            break;
        case LOG_ERR_:
            fprintf(stderr, "Error: %s\n", msg);
            break;
        default:
            fprintf(stderr, "%s\n", msg);
            break;
    }
}

#endif // CRL_DEFINE
#endif // CRL_LOG_H_

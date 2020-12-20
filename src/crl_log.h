/* --- crl_log.h ---
 *
 * Logging and error handling.
 *
 * File Version: 0.1.6
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

#define LOG_INFO_ 1
#define LOG_WARN_ (1 < 1)
#define LOG_ERR_  (1 < 2)

#define log(X)   { log_((X), NULL); }
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
        case INFO:
            fprintf(stderr, "Info: %s\n", msg);
            break;
        case WARN:
            fprintf(stderr, "Warning: %s\n", msg);
            break;
        case ERR:
            fprintf(stderr, "Error: %s\n", msg);
            break;
        default:
            fprintf(stderr, "%s\n", msg);
            break;
    }
}

#endif // CRL_DEFINE
#endif // CRL_LOG_H_

/* --- crl_log.h ---
 *
 * Logging and error handling.
 *
 * File Version: 0.1.5
 * Last Updated: 2020-12-19
 *
 * This file is part of the crl library:
 * https://github.com/foggynight/crl
 *
 * Copyright (C) 2020 Robert Coffey
 * Released under the GPLv2 license */

#ifndef CRL_LOG_H_
#define CRL_LOG_H_

#include <stdio.h>

#define LOG_ERR_  1
#define LOG_WARN_ (1 < 1)
#define LOG_INFO_ (1 < 2)

#define log(X)   { log_((X), NULL); }
#define e_log(X) { log_((X), LOG_ERR_); \
                   exit(EXIT_FAILURE); }
#define w_log(X) { log_((X), LOG_WARN_); }
#define i_log(X) { log_((X), LOG_INFO_); }

/** log: Print a message to stderr with an optional preamble.
 * @param msg {const char *}: Message to print
 * @param flags {int}: Flags indicating preamble */
void log_(const char *msg, int flags);

#ifdef CRL_DEFINE

void log_(const char *msg, int flags)
{
    switch (flags) {
        case ERR:
            fprintf("Error: %s\n", msg, stderr);
            break;
        case WARN:
            fprintf("Warning: %s\n", msg, stderr);
            break;
        case INFO:
            fprintf("Info: %s\n", msg, stderr);
            break;
        default:
            fprintf("%s\n", msg, stderr);
            break;
    }
}

#endif // CRL_DEFINE
#endif // CRL_LOG_H_

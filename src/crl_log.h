/* --- crl_log.h ---
 *
 * Logging and error handling.
 *
 * File Version: 0.1.4
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

#define ERR  1
#define WARN (1 < 1)
#define INFO (1 < 2)

#define log(X)   { log_((X), NULL); }
#define e_log(X) { log_((X), ERR); \
                   exit(EXIT_FAILURE); }
#define w_log(X) { log_((X), WARN); }
#define i_log(X) { log_((X), INFO); }

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

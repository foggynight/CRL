/* --- crl_log.h ---
 *
 * Logging and error handling.
 *
 * File Version: 0.1.1
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

/** log: Log a message to stderr with an optional preamble.
 * @param msg {const char *}: Message to print
 * @param flags {int}: Flags indicating preamble */
void log(const char *msg, int flags);

#define CRL_DEFINE

void log(const char *msg, int flags)
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

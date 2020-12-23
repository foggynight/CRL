/* --- rtb_log.h ---
 *
 * Macros for print logging to the stderr stream.
 *
 * Define the RTB_NO_EXIT macro before including this header to prevent
 * the rtb_elog macros from causing the program to exit.
 *
 * This file is part of the rtb library:
 * https://github.com/foggynight/rtb
 *
 * File Version: 0.3.1
 * First Commit: 2020-12-19
 * Last Updated: 2020-12-23
 *
 * Copyright (C) 2020 Robert Coffey
 * Released under the MIT license */

#ifndef RTB_LOG_H_
#define RTB_LOG_H_

#include <stdarg.h>
#include <stdio.h>

#define RTB_LOG_INFO_ 0x1
#define RTB_LOG_WARN_ 0x2
#define RTB_LOG_ERR_  0x4

#define rtb_log(X)  do { fprintf(stderr, "%s\n", (X)); } while (0)
#define rtb_ilog(X) do { fprintf(stderr, "Info: %s\n", (X)); } while (0)
#define rtb_wlog(X) do { fprintf(stderr, "Warning: %s\n", (X)); } while (0)

#define rtb_logf(...)  do { fprintf(stderr, __VA_ARGS__); } while (0)
#define rtb_ilogf(...) do { fprintf(stderr, "Info: " __VA_ARGS__); } while (0)
#define rtb_wlogf(...) do { fprintf(stderr, "Warning: " __VA_ARGS__); } while (0)

#ifndef RTB_NO_EXIT
#include <stdlib.h>
#define rtb_elog(X)    do { fprintf(stderr, "Error: %s\n", (X)); exit(EXIT_FAILURE); } while (0)
#define rtb_elogf(...) do { fprintf(stderr, "Error: " __VA_ARGS__); exit(EXIT_FAILURE); } while (0)
#endif // RTB_NO_EXIT

#ifdef RTB_NO_EXIT
#define rtb_elog(X)    do { fprintf(stderr, "Error: %s\n", (X)); } while (0)
#define rtb_elogf(...) do { fprintf(stderr, "Error: " __VA_ARGS__); } while (0)
#endif // RTB_NO_EXIT

#endif // RTB_LOG_H_

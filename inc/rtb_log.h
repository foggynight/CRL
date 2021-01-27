/**
 * rtb_log.h - v0.1.6 - Macros for printing to the stderr stream
 *
 * Define the RTB_NO_EXIT macro before including this header to prevent
 * the elog macros from calling exit.
 *
 * This file is part of the rtb library: http://foggynight.ca/git/rtb
 *
 * Copyright (C) 2020-2021 Robert Coffey
 * Released under the MIT license
 **/

#ifndef RTB_LOG_H_
#define RTB_LOG_H_

#include <stdarg.h>
#include <stdio.h>

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

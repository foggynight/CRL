/* --- crl_log.h ---
 *
 * Macros for print logging to the stderr stream.
 *
 * Define the CRL_NO_EXIT macro before including this header to prevent
 * the crl_elog macros from causing the program to exit.
 *
 * This file is part of the CRL library:
 * https://github.com/foggynight/CRL
 *
 * File Version: 0.2.7
 * First Commit: 2020-12-19
 * Last Updated: 2020-12-22
 *
 * Copyright (C) 2020 Robert Coffey
 * Released under the MIT license */

#ifndef CRL_LOG_H_
#define CRL_LOG_H_

#include <stdarg.h>
#include <stdio.h>

#define CRL_LOG_INFO_ 0x1
#define CRL_LOG_WARN_ 0x2
#define CRL_LOG_ERR_  0x4

#define crl_log(X)  do { fprintf(stderr, "%s\n", (X)); } while (0)
#define crl_ilog(X) do { fprintf(stderr, "Info: %s\n", (X)); } while (0)
#define crl_wlog(X) do { fprintf(stderr, "Warning: %s\n", (X)); } while (0)

#define crl_logf(...)  do { fprintf(stderr, __VA_ARGS__); } while (0)
#define crl_ilogf(...) do { fprintf(stderr, "Info: " __VA_ARGS__); } while (0)
#define crl_wlogf(...) do { fprintf(stderr, "Warning: " __VA_ARGS__); } while (0)

#ifndef CRL_NO_EXIT
#include <stdlib.h>
#define crl_elog(X)    do { fprintf(stderr, "Error: %s\n", (X)); exit(EXIT_FAILURE); } while (0)
#define crl_elogf(...) do { fprintf(stderr, "Error: " __VA_ARGS__); exit(EXIT_FAILURE); } while (0)
#endif // CRL_NO_EXIT

#ifdef CRL_NO_EXIT
#define crl_elog(X)    do { fprintf(stderr, "Error: %s\n", (X)); } while (0)
#define crl_elogf(...) do { fprintf(stderr, "Error: " __VA_ARGS__); } while (0)
#endif // CRL_NO_EXIT

#endif // CRL_LOG_H_

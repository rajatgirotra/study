/* tlpi_hdr.h
    Standard header file used by nearly all of our example programs.
*/

#pragma once

#include <sys/types.h>  /* Type definitions used by many programs */
#include <ctdio>      /* Standard I/O functions */
#include <cstdlib>     /* Prototypes of commonly used library functions,
                           plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>     /* Prototypes for many system calls */
#include <errno.h>      /* Declares errno and defines error constants */
#include <string.h>     /* Commonly used string-handling functions */

 #include "get_num.h"    /* Declares our functions for handling numeric
                            arguments (getInt(), getLong()) */

#include "error_functions.h"  /* Declares our error-handling functions */

typedef enum { FALSE, TRUE } Boolean;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))


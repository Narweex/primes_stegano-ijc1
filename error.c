    // error.c
    // Řešení IJC-DU1, příklad B), 29.2 2025
    // Autor: Jakub Kříž, FIT
    // Přeloženo: gcc 19.3
    
    /**
     * @file error.c 
     * @brief .c file for error and warning module
     */
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "error.h"

void warning(const char *fmt, ...){
    va_list args;
    fprintf(stderr, "Warning: ");
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
}

void error_exit(const char *fmt, ...){
    va_list args;
    fprintf(stderr, "Error: ");
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    exit(1);
}
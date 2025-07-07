    // error.h
    // Řešení IJC-DU1, příklad B), 28.2 2025
    // Autor: Jakub Kříž, FIT
    // Přeloženo: gcc 19.3
    
/**
 * @file error.h
 * @brief header file for error and warning printing module
 */
#ifndef ERROR_H
#define ERROR_H
#include <stdarg.h>

/**
 * @brief Prints out a warning message, works the same way as printf regarding args
 */
extern void warning(const char *fmt, ...);
/**
 * @brief Exits the program with a error message
 */
extern void error_exit(const char *fmt, ...);

#endif
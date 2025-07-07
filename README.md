IJC-DU1 Project Summary (C, FIT VUT)
The project consists of implementing a custom bitset library in C (bitset.h) with macros or inline functions (based on USE_INLINE) and efficient memory use. It includes a primes.c program using the Sieve of Eratosthenes to find the last 10 primes up to 333 million, and measures runtime with clock().

Also required:

An error module (error.h, error.c) for standardized error handling.

A PPM image module (ppm.h, ppm.c) for reading binary P6 format images.

A steg-decode.c program to extract a hidden null-terminated UTF-8 message stored in LSBs at prime byte positions starting from 101.

Everything must compile with a Makefile (targets: primes, primes-i, steg-decode) and follow ISO C11. Final submission is a .zip file with all .c, .h files and the Makefile.

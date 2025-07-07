    // primes.c
    // Řešení IJC-DU1, příklad a), 2.3.2025
    // Autor: Jakub Kříž, FIT
    // Přeloženo: gcc 19.3

    #include <stdio.h>
    #include "bitset.h"
    #include <time.h>
    #include "error.h"
    #include "eratosthenes.h"
    #define PRINT_LIMIT 10
    #define BITSET 333000000

    void print_primes(bitset_t pole) {
        bitset_index_t last_numbers[PRINT_LIMIT];
        bitset_index_t j = 0;
        bitset_index_t size = bitset_size(pole)-1;

        for (bitset_index_t i = size; i > 0 && j < PRINT_LIMIT; i--) {
            if (bitset_getbit(pole, i)) {
                last_numbers[j++] = i;
            }
        }
    
        for (int i = PRINT_LIMIT-1; i >= 0; i--) {
            printf("%ld\n", last_numbers[i]);
        }
    }

int main() {
    //Initialize the start time
    clock_t start_time = clock();
    
    bitset_alloc(bitfield, BITSET);

    Eratosthenes(bitfield);
    print_primes(bitfield);
    bitset_free(bitfield);
    //substract and print time
    clock_t endtime = clock();
    warning("Time=%.3g\n", (double)(endtime-start_time)/CLOCKS_PER_SEC);

    return 0;
}

    // eratosthenes.h
    // Řešení IJC-DU1, příklad a, 15.3 2025
    // Autor: Jakub Kříž, FIT
    // Přeloženo: gcc 19.2
    // 
    /**
     * @file bitset.h
     * @brief module for including the Eratosthenes function
     */
#include "bitset.h" // Include the header file where bitset_t is defined
#include <stdio.h>
#include <math.h>
/**
 * @brief Sets all the bits to true and performs the sieve of eratosthenes algorithm. All the primes left are set to 1
 * @param pole bitset to apply the algorithm to
 */
void Eratosthenes(bitset_t bitset) {

    bitset_index_t limit = sqrt(bitset_size(bitset));
    bitset_fill(bitset, 1);

    bitset_setbit(bitset, 0, 0);
    bitset_setbit(bitset, 1, 0);

    for(bitset_index_t i = 2; i <= limit; i++) {    
       unsigned int bit = bitset_getbit(bitset, i);
       if(bit){
           for(bitset_index_t j = i*i; j < bitset_size(bitset); j += i) {
               bitset_setbit(bitset, j, 0);   
               
            }  
        }
    }
}
    // bitset.h
    // Řešení IJC-DU1, příklad a, 1.3.2025
    // Autor: Jakub Kříž, FIT
    // Přeloženo: gcc 19.3

    /**
     * @file bitset.h
     * @brief header file for operations over bitfields
     */

//Define inclusion guard
#ifndef BITSET_H
#define BITSET_H
//inclusions
#include <stddef.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include "error.h"
#include <stdbool.h>

/**
 * @brief Structure representing the bitset
 */
typedef unsigned long *bitset_t;

/**
 * @brief Index used for iterations over bitfields
 */
typedef unsigned long bitset_index_t;

/*Counting the number of unsigned longs necessary to save num_of_bits*/
#define num_ulongs(num_of_bits) (num_of_bits + sizeof(bitset_t) * CHAR_BIT - 1) / (sizeof(bitset_t) * CHAR_BIT) + ((num_of_bits + sizeof(bitset_t) * CHAR_BIT - 1) % (sizeof(bitset_t) * CHAR_BIT) != 0)


/**
 * @brief Creates a bitset with the name jmeno_pole and the size of size
 * @param name name of the bitset
 * @param size size of the bitset 
 */
#define bitset_create(name, size) \
    do { \
        static_assert(size > 0, "Size must be greater than 0");\
        bitset_index_t name[num_ulongs(size)] = {size};\
    } while (0)

/**
 * @brief Allocates a bitset with the name jmeno_pole and the submitted size
 * @param name name of the bitset
 * @param size size of the bitset
 */
#define bitset_alloc(name, size) \
    assert(size > 0); \
    /*Allocating 1 more element to store the size of the bitset*/\
    bitset_t name = calloc(num_ulongs(size) + 1, sizeof(bitset_index_t)); \
    name[0] = size;


#ifndef USE_INLINE
/**
 * @brief Frees the memory of the submitted bitfield
 * @param bitfield pointer to the bitfield
 */
#define bitset_free(bitfield) free(bitfield);

/**
 * @brief Returns the size of submitted bitfield
 * @param bitfield pointer to the bitfield
 * @return returns the size of the submitted bitfield
 */
#define bitset_size(bitfield) bitfield[0]

/**
 * @brief Sets all the bits in the bitfield to the submitted value
 * @param bitfield pointer to the bitfield
 * @param boolean value to set the bits to
 */
#define bitset_fill(bitfield, boolean)\
do {\
    bitset_index_t ins_value = boolean ? ULONG_MAX : 0;\
    for (bitset_index_t i = 1; i < num_ulongs(bitfield[0]); i++) {\
        bitfield[i] = ins_value;\
        }\
    } while (0)

/**
 * @brief Sets the bit at the index to the submitted value
 * @param bitfield pointer to the bitfield
 * @param index index of the bit to set
 * @param value value to set the bit to
 */
#define bitset_setbit(bitfield, index, value)\
do {  \
    bitset_index_t location = index + sizeof(unsigned long) * CHAR_BIT;\
    \
    int array_index = location / (sizeof(unsigned long) * CHAR_BIT);\
    \
    if (location >= bitset_size(bitfield) + sizeof(unsigned long) * CHAR_BIT) {\
        error_exit("%s: Array out of bounds"); \
    }\
    else {\
        bitset_index_t val = 1L << (location % (sizeof(unsigned long) * CHAR_BIT));\
        if (value) {\
            bitfield[array_index] |= val;\
        }\
        else {\
            val = ~val;\
            bitfield[array_index] &= val;\
        }\
    } \
} while(0);

/**
 * @brief Returns the value of the bit at the index
 * @param bitfield pointer to the bitfield
 * @param index index of the bit to get
 */
#define bitset_getbit(bitfield, index)\
((bitfield[(index / (sizeof(bitset_index_t) * CHAR_BIT)) + 1UL] & (1UL << (index % (sizeof(bitset_index_t) * CHAR_BIT)))) != false)


/*Inline functions when USE_INLINE is defined*/
#else

/** 
 * @brief Returns the size of submitted bitfield
 * @param bitfield pointer to the bitfield
 * @return returns the size of submitted bitfield
*/
inline size_t bitset_size(const bitset_t bitfield){
    return bitfield[0];
}

/**
 * @brief Sets all the bits in the bitfield to the submitted value
 * @param bitfield pointer to the bitfield
 * @param value value to set the bits to
 */
inline void bitset_fill(bitset_t bitfield, bool value){
    size_t ins_value = value ? ULONG_MAX : 0;                     \
        for (unsigned i = 0; i < num_ulongs(bitfield[0]); ++i){\
            bitfield[i] = ins_value;\
        } }


/**
 * @brief Sets the bit at the index to the submitted value
 * @param bitfield pointer to the bitfield
 * @param index index of the bit to be set
 * @param value value to set the bit to
 */
inline void bitset_setbit(bitset_t bitfield, bitset_index_t index, bool value){
    if(index >= bitfield[0]){
        error_exit("Bitset setbit");
    }
    size_t array_index = index / (CHAR_BIT * sizeof(unsigned long));
    size_t bit_index = index % (CHAR_BIT * sizeof(unsigned long));
    if (value) {
        bitfield[array_index] |= (1UL << bit_index);  
    } else {
        bitfield[array_index] &= ~(1UL << bit_index); 
    }
}

/**
 * @brief gets the value of a certain bit based on the index parameter
 * @param bitfield bitset to search in
 * @param index which bit to be targeted
 */
inline bool bitset_getbit(const bitset_t bitfield, bitset_index_t index){
    if(index >= bitfield[0]){
        error_exit("Bitset getbit");
    }
    size_t array_index = index / (CHAR_BIT * sizeof(unsigned long));
    size_t bit_index = index % (CHAR_BIT* sizeof(unsigned long));
    return (bitfield[array_index] & (1UL << bit_index)) != 0; 
}

/**
 * @brief frees the memory used by bitset and sets the pointer to NULL
 * @param bitfield bitset to be freed
 */
inline void bitset_free(bitset_t bitfield){
    free(bitfield);
    bitfield = NULL;
}
#endif
#endif
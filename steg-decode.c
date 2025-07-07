// steg-decode.c
// Řešení IJC-DU1, příklad B), 15.3.2025
// Autor: Jakub Kříž, FIT
// Přeloženo: gcc 19.3

#include "ppm.h"
#include "error.h"
#include "bitset.h"
#include "eratosthenes.h"
#include <stdio.h>
#define START_PRIME 101


int main(int argc, char **argv) {
    if (argc != 2) {//must be atleast two arguments
        error_exit("Invalid number of arguments\n");
    }

    struct ppm *image = ppm_read(argv[1]);
    if (image == NULL) {
        error_exit("Failed to load image\n");
    }

    bitset_alloc(bitset, COLOR_CHANNELS * image->xsize * image->ysize);
    
    Eratosthenes(bitset);

   /*print out the hidden message*/
   int bit = 0;
   char msg[500];
   int msg_byte = 0;
   char c = 0;
   for(bitset_index_t i = START_PRIME; i < bitset_size(bitset); i++){
       if(bitset_getbit(bitset, i)){
           c |= (image->data[i] & 1) << bit++;

           if(bit == 8){
               msg[msg_byte] = c;
               msg_byte++;
               bit = 0;
               if(c =='\0'){
                   break;
               }
               c = 0;
           }
       }
   }
   printf("The message is: %s\n", msg);

    bitset_free(bitset);
    ppm_free(image);
    return 0;
}

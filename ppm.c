    // ppm.c
    // Řešení IJC-DU1, příklad B), 28.2 2025
    // Autor: Jakub Kříž, FIT
    // Přeloženo: gcc 12.2

  #include "error.h"
  #include <stdio.h>
  #include <stdlib.h>
  #include "ppm.h"
  #include <ctype.h>

  struct ppm* ppm_read(const char* filename) {
    FILE *file = fopen(filename, "r");
        if (!file) {
            error_exit("File not found");
        }

//reading the magic number
char magic[2];
if (fscanf(file, "%2s", magic) != 1) {
    fclose(file);
    error_exit("Invalid PPM format (magic number)");
}

//reading the dimensions and max value at the beginning of the file
unsigned int xsize, ysize, maxval;
if (fscanf(file, "%u %u %u", &xsize, &ysize, &maxval) != 3) {
    fclose(file);
    error_exit("Invalid PPM header");
}

//skipping the space or newline right before the binary data
int c;
do {
    c = fgetc(file);
} while (isspace(c));
ungetc(c, file);

//allocate the necassary memory for the structure to bve returned
struct ppm *p = (struct ppm*)malloc(sizeof(struct ppm) + COLOR_CHANNELS * xsize * ysize);
if (p == NULL) {
    fclose(file);
    error_exit("Memory allocation failed");
}

p->xsize = xsize;
p->ysize = ysize;

// reading of the binary data
size_t bytes_read = fread(p->data, 1, COLOR_CHANNELS * xsize * ysize, file);
if (bytes_read != COLOR_CHANNELS * xsize * ysize) {
    free(p);
    fclose(file);
    error_exit("Unexpected end of file while reading image data");
}
fclose(file);
return p;

}

void ppm_free(struct ppm* p){
    free(p);
}
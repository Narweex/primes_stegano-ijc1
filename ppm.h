    // ppm.h
    // Řešení IJC-DU1, příklad B), 12.3 2025
    // Autor: Jakub Kříž, FIT
    // Přeloženo: gcc 20.3
     

#define COLOR_CHANNELS 3
#ifndef PPM_H
#define PPM_H
    struct ppm{
        unsigned int xsize;
        unsigned int ysize;
        char data[]; //rgb data 3*xsize*ysize
    };
    /**
     * @brief reads the contents of the filename and returns a structure ppm filled with data
     * @param filename name of the file to be scanned. Must be a valid .ppm file
     * @return returns a pointer to allocated ppm structure
     */
    extern struct ppm* ppm_read(const char *filename);
    /**
     * @brief frees the submitted ppm structure
     * @param p pointer to the structure to be freed
     */
    extern void ppm_free(struct ppm *p);
    

#endif
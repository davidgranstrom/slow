#ifndef IO_H
#define IO_H

#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read a file and return the data and read size.
 * 
 * If the function is successful a pointer to newly allocated
 * memory will be written to `data` and it's size in bytes
 * returned in `size`.
 * 
 * If the function fails the errno value is returned and
 * no values are written to `data` or `size`.
 */
int read_stream(FILE *f, char **data, size_t *size);

#ifdef __cplusplus
}
#endif

#endif /* IO_H */

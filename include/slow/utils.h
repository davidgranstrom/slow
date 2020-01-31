#ifndef SLOW_UTILS_H
#define SLOW_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Read a stream and return the data and read size.
 * 
 * If the function is successful a pointer to newly allocated
 * memory will be written to `data` and it's size in bytes
 * returned in `size`.
 * 
 * If the function fails the errno value is returned and
 * no values are written to `data` or `size`.
 *
 * @param f File handle.
 * @param data Pointer to the read data.
 * @param size Number of bytes read.
 */
int read_stream(FILE *f, char **data, size_t *size);

/**
 * @brief Sleep for some time.
 * @param millis Time in milliseconds.
 */
void slow_sleep(int millis);

/**
 * @brief Get a random value.
 * @returns A random value between 0.0 - 1.0.
 */
double slow_random(void);

#ifdef __cplusplus
}
#endif

#endif /* SLOW_UTILS_H */

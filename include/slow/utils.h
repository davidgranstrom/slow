#ifndef SLOW_UTILS_H
#define SLOW_UTILS_H

#include <time.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

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

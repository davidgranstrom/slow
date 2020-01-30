#include "slow/utils.h"

#define NANO_SECONDS 1000000

void slow_sleep(int millis)
{
  struct timespec t1 = {0};
  struct timespec t2 = {0};

  t1.tv_sec = 0;
  t1.tv_nsec = millis * NANO_SECONDS;

  nanosleep(&t1, &t2);
}

double slow_random()
{
  return drand48();
}

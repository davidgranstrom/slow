/*
slow - like cat but slower
Copyright (C) 2020 David Granström

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "slow/utils.h"

#define CHUNK_SIZE 512
#define NANO_SECONDS 1000000

int read_stream(FILE *f, char **data, size_t *size)
{
  size_t readsz, totalsz = 0, memsz;
  char *buf, *tmpbuf;
  int ret = 0;
  clearerr(f);
  memsz = CHUNK_SIZE;
  buf = malloc(memsz);
  if (buf != NULL) {
    while (ret == 0) {
      readsz = fread(buf + totalsz, 1, CHUNK_SIZE, f);
      if (ferror(f)) {
        ret = errno;
      } else {
        totalsz += readsz;
        if (totalsz >= memsz) {
          memsz += CHUNK_SIZE;
          tmpbuf = realloc(buf, memsz);
          if (tmpbuf == NULL) {
            ret = errno;
          } else
            buf = tmpbuf;
        }
      }
      if (readsz != CHUNK_SIZE)
        break;
    }
  } else
    ret = errno;
  if (ret) {
    free(buf);
    return ret;
  }
  *data = buf;
  *size = totalsz;
  return 0;
}

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

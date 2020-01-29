#include <stdio.h>
#include "slow/io.h"

int main(int argc, char **argv)
{
  char *data = NULL;
  size_t num_bytes = 0;
  int err = read_stream(stdin, &data, &num_bytes);
  char c = 0;
  while ((c = *data++) != '\0') {
    printf("%c", c);
  }
  return 0;
}

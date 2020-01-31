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

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "slow/utils.h"

struct Options {
  int delay;
  int jitter;
  bool line_output;
};

static void print_usage()
{
  printf(
      "usage: slow [file] [-djlh]\n\n"
      "example: ls | slow\n\n"
      "options:\n"
      "-d --delay    [default 15] Delay time in milliseconds\n"
      "-j --jitter   [default 0] Apply random delay jitter\n"
      "-l --line     Display line by line output instead of char by char\n"
      "-h --help     Show this help\n"
      );
}

static void parse_args(int argc, char **argv, struct Options *opts)
{
  if (argc > 1) {
    for (int i = 0; i < argc; i++) {
      if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--delay") == 0) {
        opts->delay = (int)strtol(argv[i + 1], (char **)NULL, 10);
      }
      if (strcmp(argv[i], "-j") == 0 || strcmp(argv[i], "--jitter") == 0) {
        opts->jitter = (int)strtol(argv[i + 1], (char **)NULL, 10);
      }
      if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--line") == 0) {
        opts->line_output = true;
      }
      if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
        print_usage();
        exit(EXIT_SUCCESS);
      }
    }
  }
}

static void delay(int d, int j)
{
  slow_sleep(d);
  fflush(stdout);
  if (j > 0) {
    int amount = j * slow_random();
    slow_sleep(amount);
  }
}

static bool is_filename(char *s)
{
  if (strcmp(s, "-d") == 0 || strcmp(s, "--delay") == 0) 
    return false;
  if (strcmp(s, "-j") == 0 || strcmp(s, "--jitter") == 0) 
    return false;
  if (strcmp(s, "-l") == 0 || strcmp(s, "--line") == 0) 
    return false;
  if (strcmp(s, "-h") == 0 || strcmp(s, "--help") == 0) 
    return false;
  return true;
}

int main(int argc, char **argv)
{
  struct Options opts = {
    .delay = 15,
    .jitter = 0,
    .line_output = false,
  };

  parse_args(argc, argv, &opts);

  FILE *f = stdin;
  if (argc > 1) {
    char *first_arg = argv[1];
    if (is_filename(first_arg)) {
      f = fopen(first_arg, "rb");
      if (f == NULL)
        exit(EXIT_FAILURE);
    }
  }

  char *data = NULL;
  size_t nread = 0;
  int err = read_stream(f, &data, &nread);
  if (err != 0) {
    fclose(f);
    exit(EXIT_FAILURE);
  }

  if (!opts.line_output) {
    char c = 0;
    for (size_t i = 0; i < nread; i++) {
      printf("%c", data[i]);
      delay(opts.delay, opts.jitter);
    }
  } else {
    char *token = NULL;
    while ((token = strsep(&data, "\n\r")) != NULL) {
      printf("%s\n", token);
      delay(opts.delay, opts.jitter);
    }
  }

  fclose(f);
  free(data);
  return EXIT_SUCCESS;
}

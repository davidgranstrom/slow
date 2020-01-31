#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "slow/io.h"
#include "slow/utils.h"

struct options {
  int delay;
  int jitter;
  bool line_output;
  bool help;
};

static void parse_args(int argc, char **argv, struct options *opts)
{
  if (argc > 1) {
    for (int i = 0; i < argc; i++) {
      if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--delay") == 0) {
        opts->delay = (int)strtol(argv[i + 1], (char **)NULL, 10);
      }
      if (strcmp(argv[i], "-j") == 0 || strcmp(argv[i], "--jitter") == 0) {
        opts->jitter = (int)strtol(argv[i + 1], (char **)NULL, 10);
      }
      if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--lines") == 0) {
        opts->line_output = true;
      }
      if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
        printf(
            "usage: slow [-djl] [file]\n"
            "example: ls | slow\n"
            "options:\n"
            "-d --delay    [default 15] Delay time in milliseconds\n"
            "-j --jitter   [default 0] Apply random delay jitter\n"
            "-l --lines    Display line by line output instead of char by char\n"
            "-h --help     Show this help\n"
            );
        opts->help = true;
        break; // no need to continue parsing args
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

int main(int argc, char **argv)
{
  struct options opts = {
    .delay = 15,
    .jitter = 0,
    .line_output = false,
    .help = false,
  };

  parse_args(argc, argv, &opts);

  if (opts.help)
    exit(EXIT_SUCCESS);

  FILE *f = stdin;
  if (argc > 1) {
    char *last_arg = argv[argc-1];
    if (last_arg[0] != '-') {
      f = fopen(last_arg, "rb");
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

  free(data);
  return EXIT_SUCCESS;
}

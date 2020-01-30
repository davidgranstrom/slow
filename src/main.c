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
    return 0;

  char *data = NULL;
  size_t num_bytes = 0;
  int err = read_stream(stdin, &data, &num_bytes);
  char c = 0;
  while ((c = *data++) != '\0') {
    printf("%c", c);
    slow_sleep(opts.delay);
    fflush(stdout);
  }
  return 0;
}

#include <stdlib.h>
#include <time.h>
#include "caser.h"
#include "args.h"

int main(int argc, char *argv[])
{
  struct arguments arguments;

  arguments.scheme = PASCAL_CASE_SCHEME;
  arguments.casing = PRESERVE_CASE;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  processArgs(arguments);

  return EXIT_SUCCESS;
}

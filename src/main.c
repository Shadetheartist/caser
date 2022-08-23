#include <stdlib.h>
#include <time.h>
#include "caser.h"
#include "args.h"

int main(int argc, char *argv[])
{
  struct arguments arguments;

  arguments.scheme = NO_SCHEME;
  arguments.casing = PRESERVE_CASE;
  arguments.fileMode = false;
  arguments.paths = NULL;
  arguments.numPaths = 0;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  processArgs(arguments);

  return EXIT_SUCCESS;
}

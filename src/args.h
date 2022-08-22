#ifndef __ARGS_H__
#define __ARGS_H__

#include <stdio.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <argp.h>
#include <stdbool.h>
#include <string.h>
#include "engine.h"

#define CASING_USAGE_INSTRUCTIONS "Lower case ('l'), upper case ('u') or preserve case ('p')."

struct arguments
{
  Scheme scheme;
  LetterCase casing;
  char **paths;
  int numPaths;
  bool fileMode;
};

extern struct argp argp;

#endif // __ARGS_H__

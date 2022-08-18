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

extern const char *argp_program_version;
extern const char *argp_program_bug_address;
extern char doc[];
extern char args_doc[];
extern struct argp_option options[];

struct arguments
{
  Scheme scheme;
  LetterCase casing;
  char **paths;
  int numPaths;
  bool renameFiles;
};

int getCasingOption(char *arg);

error_t parse_opt(int key, char *arg, struct argp_state *state);

extern struct argp argp;

#endif // __ARGS_H__

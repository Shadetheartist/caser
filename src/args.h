#ifndef __ARGS_H__
#define __ARGS_H__

#include <stdio.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <argp.h>
#include <stdbool.h>
#include <string.h>

#define CASING_USAGE_INSTRUCTIONS "Lower case ('l'), upper case ('u') or preserve case ('p')."

extern const char *argp_program_version;
extern const char *argp_program_bug_address;
extern char doc[];
extern char args_doc[];
extern struct argp_option options[];

struct arguments
{
  enum
  {
    SNAKE_CASE_MODE,
    CAMEL_CASE_MODE,
    PASCAL_CASE_MODE,
    TITLE_CASE_MODE,
  } mode;

  enum
  {
    PRESERVE_CASE,
    TO_LOWER_CASE,
    TO_UPPER_CASE,
  } casing;

  char **paths;
  int numPaths;
};

int getCasingOption(char *arg);

error_t parse_opt(int key, char *arg, struct argp_state *state);

extern struct argp argp;

#endif // __ARGS_H__

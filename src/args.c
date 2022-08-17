#include <stdio.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <argp.h>
#include <stdbool.h>
#include <string.h>
#include "args.h"

const char *argp_program_version = "caser 1.0.0";
const char *argp_program_bug_address = "<b.derehemi@gmail.com>";
char doc[] = "Converts file names to a standard casing scheme.";
char args_doc[] = "[FILENAME]...";
struct argp_option options[] = {
    {"snake", 's', 0, 0, "Rename to snake_case"},
    {"camel", 'c', 0, 0, "Rename to camelCase"},
    {"pascal", 'p', 0, 0, "Rename to PascalCase"},
    {"title", 't', 0, 0, "Rename to Title Case"},
    {"casing", 'i', "l|u|p", 0, CASING_USAGE_INSTRUCTIONS},
    {0}
};


int getCasingOption(char *arg)
{
  int casingOption = tolower(*arg);
  switch (casingOption)
  {
  case 'l':
    return TO_LOWER_CASE;
  case 'u':
    return TO_UPPER_CASE;
  case 'p':
    return PRESERVE_CASE;
  default:
    return -1;
  }
}

error_t parse_opt(int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;
  switch (key)
  {
  case 's':
    arguments->mode = SNAKE_CASE_MODE;
    break;

  case 'c':
    arguments->mode = CAMEL_CASE_MODE;
    break;

  case 'p':
    arguments->mode = PASCAL_CASE_MODE;
    break;

  case 't':
    arguments->mode = TITLE_CASE_MODE;
    break;

  case 'i':
    int casingOption = getCasingOption(arg);
    if (casingOption == -1)
    {
      argp_usage(state);
    }

    arguments->casing = casingOption;
    break;

  case ARGP_KEY_ARG:
    // based on example from https://www.gnu.org/software/libc/manual/html_node/Argp-Example-4.html
    // the pointer subtraction should be ok but might be a bug for later
    arguments->paths = &state->argv[state->next - 1];
    state->next = state->argc;

    // this works because when the args run out the eval of arguments->paths[i] will be zero.
    // any other character will eval to some non zero number.
    arguments->numPaths = 0;
    for (int i = 0; arguments->paths[i]; i++)
    {
      arguments->numPaths++;
    }

    return 0;

  case ARGP_KEY_NO_ARGS:
    argp_usage(state);

  default:
    return ARGP_ERR_UNKNOWN;
  }

  return 0;
}

struct argp argp = {options, parse_opt, args_doc, doc, 0, 0, 0};

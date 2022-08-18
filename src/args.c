#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include <string.h>
#include "args.h"

const char *argp_program_version = "caser 1.0.1";
const char *argp_program_bug_address = "<b.derehemi@gmail.com>";
char doc[] = "Converts strings and file names to a standard naming convention scheme. Only works with the 'none' and 'snake' naming conventions.";
char args_doc[] = "[STRING]...";
struct argp_option options[] = {
    {"none", 'n', 0, 0, "Do not enforce a naming convention scheme."},
    {"snake", 's', 0, 0, "Convert to snake_case."},
    {"camel", 'c', 0, 0, "Convert to camelCase."},
    {"pascal", 'p', 0, 0, "Convert to PascalCase."},
    {"title", 't', 0, 0, "Convert to Title Case."},
    {"file", 'f', 0, 0, "For each input string, an attempt will be made to rename a file in the current working dir."},
    {"casing", 'i', "l|u|p", 0, CASING_USAGE_INSTRUCTIONS},
    {0}
};


int getCasingOption(char *arg)
{
  switch (*arg)
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
    arguments->scheme = SNAKE_CASE_SCHEME;
    break;

  case 'c':
    arguments->scheme = CAMEL_CASE_SCHEME;
    break;

  case 'p':
    arguments->scheme = PASCAL_CASE_SCHEME;
    break;

  case 't':
    arguments->scheme = TITLE_CASE_SCHEME;
    break;

  case 'n':
    arguments->scheme = NO_SCHEME;
    break;

  case 'f':
    arguments->renameFiles = true;
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
    return 0;

  default:
    return ARGP_ERR_UNKNOWN;
  }

  return 0;
}

struct argp argp = {options, parse_opt, args_doc, doc, 0, 0, 0};

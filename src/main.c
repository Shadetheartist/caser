#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>
#include "args.h"
#include "engine.h"

int main(int argc, char *argv[])
{
  struct arguments arguments;

  arguments.mode = SNAKE_CASE_MODE;
  arguments.casing = TO_LOWER_CASE;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  printf("arguments.mode %d\n", arguments.mode);
  printf("arguments.casing %d\n", arguments.casing);
  printf("paths:\n");

  char *tokenBuffer[MAX_TOKENS] = {0};
  char stringBuffer[PATH_MAX] = {0};

  for (int i = 0; i < arguments.numPaths; i++)
  {
    memset(tokenBuffer, 0, sizeof(char *) * MAX_TOKENS);
    memset(stringBuffer, 0, sizeof(char) * PATH_MAX);
    int numTokens = tokenize(arguments.paths[i], tokenBuffer);

    switch (arguments.casing)
    {
    case TO_UPPER_CASE:
      toUpperStrInPlace(stringBuffer);
      break;

    case TO_LOWER_CASE:
      toLowerStrInPlace(stringBuffer);
      break;

    case PRESERVE_CASE:
      break;

    default:
      exit(1);
      break;
    }

    switch (arguments.mode)
    {
    case SNAKE_CASE_MODE:
      toSnakeCase(tokenBuffer, numTokens, stringBuffer);
      break;
    case CAMEL_CASE_MODE:
      toCamelCase(tokenBuffer, numTokens, stringBuffer);
      break;
    case PASCAL_CASE_MODE:
      toPascalCase(tokenBuffer, numTokens, stringBuffer);
      break;
    case TITLE_CASE_MODE:
      toTitleCase(tokenBuffer, numTokens, stringBuffer);
      break;
    }

    printf("%s -> %s\n", arguments.paths[i], stringBuffer);

    for (int j = 0; j < MAX_TOKENS; j++)
    {
      if (tokenBuffer[j] == NULL)
      {
        break;
      }

      free(tokenBuffer[j]);
      tokenBuffer[j] = NULL;
    }
  }

  return EXIT_SUCCESS;
}

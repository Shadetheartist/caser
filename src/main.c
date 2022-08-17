#include <stdio.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <argp.h>
#include <stdbool.h>
#include "args.h"

#define MAX_TOKENS 1024

int tokenize(char *str, char **buffer)
{
  const char *delimiters = " _";

  int len = strlen(str);
  char *tokenStr = (char *)malloc(sizeof(char) * (len + 1));
  strcpy(tokenStr, str);

  int tokenCounter = 0;
  char *ptr = strtok(tokenStr, delimiters);

  do
  {
    if (tokenCounter >= MAX_TOKENS)
    {
      fprintf(stderr, "Error: Too many tokens in '%s'.", str);
      exit(EXIT_FAILURE);
    }

    buffer[tokenCounter] = malloc(sizeof(char) * strlen(ptr));
    strcpy(buffer[tokenCounter], ptr);

    tokenCounter++;
    ptr = strtok(NULL, delimiters);
  } while (ptr != NULL);

  free(tokenStr);

  return tokenCounter;
}

void toSnakeCase(char **tokens, int numTokens, char *stringBuffer)
{
  for (int i = 0; i < numTokens; i++)
  {
    if (i > 0)
    {
      strcat(stringBuffer, "_");
    }

    strcat(stringBuffer, tokens[i]);
  }
}

void toCamelCase(char **tokens, int numTokens, char *stringBuffer)
{
  for (int i = 0; i < numTokens; i++)
  {
    if (i < 1)
    {
      tokens[i][0] = tolower(tokens[i][0]);
    }
    else
    {
      tokens[i][0] = toupper(tokens[i][0]);
    }

    strcat(stringBuffer, tokens[i]);
  }
}

void toPascalCase(char **tokens, int numTokens, char *stringBuffer)
{
  for (int i = 0; i < numTokens; i++)
  {
    tokens[i][0] = toupper(tokens[i][0]);
    strcat(stringBuffer, tokens[i]);
  }
}

void toTitleCase(char **tokens, int numTokens, char *stringBuffer)
{
  for (int i = 0; i < numTokens; i++)
  {
    tokens[i][0] = toupper(tokens[i][0]);

    if (i > 0)
    {
      strcat(stringBuffer, " ");
    }

    strcat(stringBuffer, tokens[i]);
  }
}

void toUpperStrInPlace(char *str)
{
  for (int i = 0; i < str[i]; i++)
  {
    str[i] = toupper(str[i]);
  }
}

void toLowerStrInPlace(char *str)
{
  for (int i = 0; i < str[i]; i++)
  {
    str[i] = tolower(str[i]);
  }
}

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

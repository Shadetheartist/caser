#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "engine.h"

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

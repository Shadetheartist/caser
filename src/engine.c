#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <linux/limits.h>
#include "engine.h"

char *convert(const char * const str, const Scheme scheme, const LetterCase letterCase, const char * const delimiters)
{
  const int tokenCount = countTokens(str, delimiters);

  char **tokenBuffer = (char **)calloc(tokenCount, sizeof(char *));

  char *stringBuffer = (char *)calloc(strlen(str) + 1, sizeof(char));

  if (stringBuffer == NULL)
  {
    fprintf(stderr, "Out of memory");
    exit(EXIT_FAILURE);
  }

  strcpy(stringBuffer, str);

  if (scheme == NO_SCHEME || scheme == SNAKE_CASE_SCHEME || scheme == DASH_CASE_SCHEME)
  {
    switch (letterCase)
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
      exit(EXIT_FAILURE);
      break;
    }
  }

  int numTokens = tokenize(stringBuffer, tokenBuffer, delimiters);
  char *returnString = (char *)calloc(strlen(stringBuffer) + 1, sizeof(char));

  if (returnString == NULL)
  {
    fprintf(stderr, "Out of memory");
    exit(EXIT_FAILURE);
  }

  switch (scheme)
  {
  case SNAKE_CASE_SCHEME:
    toSnakeCase(tokenBuffer, numTokens, returnString);
    break;
  case CAMEL_CASE_SCHEME:
    toCamelCase(tokenBuffer, numTokens, returnString);
    break;
  case PASCAL_CASE_SCHEME:
    toPascalCase(tokenBuffer, numTokens, returnString);
    break;
  case TITLE_CASE_SCHEME:
    toTitleCase(tokenBuffer, numTokens, returnString);
    break;
  case DASH_CASE_SCHEME:
    toDashCase(tokenBuffer, numTokens, returnString);
    break;
  case NO_SCHEME:
    break;
  default:
    exit(EXIT_FAILURE);
    break;
  }

  for (int j = 0; j < tokenCount; j++)
  {
    free(tokenBuffer[j]);
    tokenBuffer[j] = NULL;
  }

  free(tokenBuffer);
  tokenBuffer = NULL;

  return returnString;
}

int countTokens(const char *const str, const char * const delimiters)
{
  int len = strlen(str);
  char *tokenStr = (char *)malloc(sizeof(char) * (len + 1));

  if (tokenStr == NULL)
  {
    fprintf(stderr, "Out of memory");
    exit(EXIT_FAILURE);
  }

  strcpy(tokenStr, str);

  int tokenCounter = 0;
  char *ptr = strtok(tokenStr, delimiters);

  while (ptr != NULL)
  {
    tokenCounter++;
    ptr = strtok(NULL, delimiters);
  }

  free(tokenStr);

  return tokenCounter;
}

int tokenize(const char *const str, char **buffer, const char * const delimiters)
{
  int len = strlen(str);
  char *tokenStr = (char *)malloc(sizeof(char) * (len + 1));

  if (tokenStr == NULL)
  {
    fprintf(stderr, "Out of memory");
    exit(EXIT_FAILURE);
  }

  strcpy(tokenStr, str);

  int tokenCounter = 0;
  char *ptr = strtok(tokenStr, delimiters);

  while (ptr != NULL)
  {
    buffer[tokenCounter] = malloc(sizeof(char) * (strlen(ptr) + 1));

    if (buffer[tokenCounter] == NULL)
    {
      fprintf(stderr, "Out of memory");
      exit(1);
    }

    strcpy(buffer[tokenCounter], ptr);

    tokenCounter++;
    ptr = strtok(NULL, delimiters);
  }

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


void toDashCase(char **tokens, int numTokens, char *stringBuffer)
{
  for (int i = 0; i < numTokens; i++)
  {
    if (i > 0)
    {
      strcat(stringBuffer, "-");
    }

    strcat(stringBuffer, tokens[i]);
  }
}

void toCamelCase(char **tokens, int numTokens, char *stringBuffer)
{

  for (int i = 0; i < numTokens; i++)
  {
    toLowerStrInPlace(tokens[i]);

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
    toLowerStrInPlace(tokens[i]);

    tokens[i][0] = toupper(tokens[i][0]);
    strcat(stringBuffer, tokens[i]);
  }
}

void toTitleCase(char **tokens, int numTokens, char *stringBuffer)
{
  for (int i = 0; i < numTokens; i++)
  {
    toLowerStrInPlace(tokens[i]);

    tokens[i][0] = toupper(tokens[i][0]);

    if (i > 0)
    {
      strcat(stringBuffer, " ");
    }

    strcat(stringBuffer, tokens[i]);
  }
}

void toUpperStrInPlace(char * const str)
{
  for (int i = 0; str[i]; i++)
  {
    str[i] = toupper(str[i]);
  }
}

void toLowerStrInPlace(char * const str)
{
  for (int i = 0; str[i]; i++)
  {
    str[i] = tolower(str[i]);
  }
}

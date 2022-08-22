#include <stdio.h>
#include <stdlib.h>
#include "caser.h"
#include "engine.h"


const char *DELIMITERS = " _.-";
const char *FILE_MODE_DELIMITERS = " _-";

char *getLine(FILE *fp)
{
  fp = stdin;
  if (fp == NULL)
  {
    exit(EXIT_FAILURE);
  }

  char *line = NULL, *tmp = NULL;
  size_t size = 0, index = 0;
  int ch = EOF;

  while (ch)
  {
    ch = getc(stdin);

    /* Check if we need to stop. */
    if (ch == EOF || ch == '\n')
      ch = 0;

    /* Check if we need to expand. */
    if (size <= index)
    {
      size += 8;
      tmp = realloc(line, size);
      if (tmp == NULL)
      {
        free(line);
        line = NULL;
        break;
      }
      line = tmp;
    }

    /* Actually store the thing. */
    line[index++] = ch;
  }

  return line;
}

void sendToOutput(struct arguments arguments, char *inputStr, char *converted)
{
  fwrite(converted, sizeof(char) * (strlen(converted) + 1), 1, stdout);
}

char *delimiterFromArgs(struct arguments arguments)
{
  if (arguments.fileMode)
  {
    return (char*) FILE_MODE_DELIMITERS;
  }
  else
  {
    return (char*) DELIMITERS;
  }
}

void parseStdIn(struct arguments arguments)
{
  for (char *line = getLine(stdin); line != NULL; line = getLine(stdin))
  {
    if (strlen(line) == 0)
    {
      break;
    }

    char *convertedStr = convert(line, arguments.scheme, arguments.casing, delimiterFromArgs(arguments));
    sendToOutput(arguments, line, convertedStr);
    free(line);
  }
}

void processArgs(struct arguments arguments)
{
  if (arguments.numPaths < 1)
  {
    parseStdIn(arguments);
  }
  else
  {
    for (int i = 0; i < arguments.numPaths; i++)
    {
      char *convertedStr = convert(arguments.paths[i], arguments.scheme, arguments.casing, delimiterFromArgs(arguments));
      sendToOutput(arguments, arguments.paths[i], convertedStr);
      free(convertedStr);
    }
  }
}

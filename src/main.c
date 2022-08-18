#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "args.h"
#include "engine.h"

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
  if (arguments.renameFiles)
  {
    int renameResult = rename(inputStr, converted);
    if (renameResult == 0)
    {
      printf("Renamed '%s' to '%s'\n", inputStr, converted);
    }
    else
    {
      printf("Could not rename '%s' to '%s'\n", inputStr, converted);
    }
  }
  else
  {
    printf("%s\n", converted);
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

    char *convertedStr = convert(line, arguments.scheme, arguments.casing);
    sendToOutput(arguments, line, convertedStr);
    free(line);
  }
}

int main(int argc, char *argv[])
{
  struct arguments arguments;

  arguments.scheme = PASCAL_CASE_SCHEME;
  arguments.casing = PRESERVE_CASE;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  if (arguments.numPaths < 1)
  {
    parseStdIn(arguments);
  }
  else
  {
    for (int i = 0; i < arguments.numPaths; i++)
    {
      char *convertedStr = convert(arguments.paths[i], arguments.scheme, arguments.casing);
      sendToOutput(arguments, arguments.paths[i], convertedStr);
      free(convertedStr);
    }
  }

  return EXIT_SUCCESS;
}

#ifndef __ENGINE_H__
#define __ENGINE_H__

#define MAX_TOKENS 1024

typedef enum
{
  NO_SCHEME,
  SNAKE_CASE_SCHEME,
  CAMEL_CASE_SCHEME,
  PASCAL_CASE_SCHEME,
  TITLE_CASE_SCHEME
} Scheme;

typedef enum
{
  PRESERVE_CASE,
  TO_LOWER_CASE,
  TO_UPPER_CASE
} LetterCase;

char *convert(char *str, Scheme scheme, LetterCase letterCase);

int tokenize(char *str, char **buffer);

void toSnakeCase(char **tokens, int numTokens, char *stringBuffer);

void toCamelCase(char **tokens, int numTokens, char *stringBuffer);

void toPascalCase(char **tokens, int numTokens, char *stringBuffer);

void toTitleCase(char **tokens, int numTokens, char *stringBuffer);

void toUpperStrInPlace(char *str);

void toLowerStrInPlace(char *str);

#endif // __ENGINE_H__
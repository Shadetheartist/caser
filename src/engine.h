#ifndef __ENGINE_H__
#define __ENGINE_H__

#define MAX_TOKENS 1024

typedef enum
{
  NO_SCHEME,
  SNAKE_CASE_SCHEME,
  DASH_CASE_SCHEME,
  CAMEL_CASE_SCHEME,
  PASCAL_CASE_SCHEME,
  TITLE_CASE_SCHEME,
} Scheme;

typedef enum
{
  PRESERVE_CASE,
  TO_LOWER_CASE,
  TO_UPPER_CASE
} LetterCase;

char *convert(const char * const str, const Scheme scheme, const LetterCase letterCase, const char * const delimiters);

int countTokens(const char * const str, const char * const delimiters);

int tokenize(const char * const str, char **buffer, const char * const delimiters);

void toSnakeCase(char **tokens, int numTokens, char *stringBuffer);

void toDashCase(char **tokens, int numTokens, char *stringBuffer);

void toCamelCase(char **tokens, int numTokens, char *stringBuffer);

void toPascalCase(char **tokens, int numTokens, char *stringBuffer);

void toTitleCase(char **tokens, int numTokens, char *stringBuffer);

void toUpperStrInPlace(char * const str);

void toLowerStrInPlace(char * const str);

#endif // __ENGINE_H__
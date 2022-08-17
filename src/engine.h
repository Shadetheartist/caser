#ifndef __ENGINE_H__
#define __ENGINE_H__

#define MAX_TOKENS 1024

int tokenize(char *str, char **buffer);

void toSnakeCase(char **tokens, int numTokens, char *stringBuffer);

void toCamelCase(char **tokens, int numTokens, char *stringBuffer);

void toPascalCase(char **tokens, int numTokens, char *stringBuffer);

void toTitleCase(char **tokens, int numTokens, char *stringBuffer);

void toUpperStrInPlace(char *str);

void toLowerStrInPlace(char *str);

#endif // __ENGINE_H__
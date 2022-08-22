#ifndef __CASER_H__
#define __CASER_H__

#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "args.h"

extern const char * const DELIMITERS;
extern const char * const FILE_MODE_DELIMITERS;

void processArgs(struct arguments arguments);

#endif // __CASER_H__
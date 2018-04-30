#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#include "structs.h"

#ifndef FREQUENCY_DEF
#define FREQUENCY_DEF

typedef struct occurencyMapper {
  unsigned int maximumNGram;
  unsigned int **occurencies;
} occurencyMapper;

#endif

occurencyMapper* countNGrams(DNAWrapper* wrapper, unsigned int maximumNGram);


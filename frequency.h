#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#include "structs.h"

#ifndef FREQUENCY_DEF
#define FREQUENCY_DEF

typedef struct occurencyMapper {
  char *fileName;
  unsigned int maximumNGram;
  unsigned long long **occurencies;
} occurencyMapper;

#endif

occurencyMapper** mapGenome(genome* gen, unsigned int maximumNGram);
occurencyMapper* countNGrams(DNAWrapper* wrapper, unsigned int maximumNGram);


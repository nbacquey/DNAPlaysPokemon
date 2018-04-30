#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#include "structs.h"
#include "frequency.h"

occurencyMapper** mapGenome(genome* gen, unsigned int maximumNGram){
  int n = gen-> num_wrappers;
  occurencyMapper **ret = malloc(sizeof(occurencyMapper*)*n);
  
  int i;
  for(i = 0; i < n; ++i){
    ret[i] = countNGrams(gen->wrappers[i], maximumNGram);
  }
  
  return ret;
}

occurencyMapper* countNGrams(DNAWrapper* wrapper, unsigned int maximumNGram){
  occurencyMapper* ret = malloc(sizeof(occurencyMapper));
  ret-> fileName = wrapper->filePath;
  ret-> maximumNGram = maximumNGram;
  ret-> occurencies = malloc(sizeof(unsigned int*)*maximumNGram);
  
  unsigned long long masks[maximumNGram];
  
  int i;
  for(i = 0; i < maximumNGram; ++i){
    ret->occurencies[i] = calloc(1 << (2*i+2),sizeof(unsigned long long));
    masks[i] = ~(ULLONG_MAX << (2*i+2));
  }
    
  unsigned int oldIndex = wrapper->structIndex;
  unsigned int oldOffset = wrapper->baseOffset;
  
  wrapper->structIndex = 0;
  wrapper->baseOffset = 0;
  
  unsigned long long buffer = 0;
  //special treatment for N first bases
  for(i = 0; i < maximumNGram; ++i){
    buffer = (buffer << 2) + nextBase(wrapper);
    int j;
    for(j = 0; j <= i; ++j){
      unsigned long long nGram = buffer & masks[j];
      ++(ret->occurencies[j][nGram]);
    }
  }
  
  while(!wrapper->hasEnded){
    buffer = (buffer << 2) + nextBase(wrapper);
    for(i = 0; i < maximumNGram; ++i){
      unsigned long long nGram = buffer & masks[i];
      ++(ret->occurencies[i][nGram]);
    }
  }
  
  wrapper->structIndex = oldIndex;
  wrapper->baseOffset = oldOffset;
  return ret;
}


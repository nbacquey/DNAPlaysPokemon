#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "structs.h"

int getBase(BD dodecuplet, int i){
  if(i >= dodecuplet.size)
    return -1;
  return (dodecuplet.bases >> (2*i)) & 0b11 ;
}

int setBase(BD *dodecuplet, int i, unsigned int base){
  if(i >= dodecuplet->size)
    return -1;
  base = base & 0b11;
  unsigned int mask = ( ~ (0b11 << (2*i))) & 0xffffff;
  dodecuplet->bases = dodecuplet->bases & mask;
  dodecuplet->bases = dodecuplet->bases | (base << (2*i));
  return 0;
}

int getAAcid(AQ quadruplet, int i){
  if(i >= quadruplet.size)
    return -1;
  return (quadruplet.acids >> (5*i)) & 0b11111 ;
}

//Functions for using DNAWrapper
char nextBase(DNAWrapper *wrapper){
  if(wrapper->hasEnded)
    return -1;
  BD basesStruct = wrapper->bases[wrapper->structIndex];
  char base = getBase(basesStruct, wrapper->baseOffset);
  unsigned int nextOffset = wrapper->baseOffset + 1;
  if(wrapper->structIndex * 12 + nextOffset >= wrapper-> totalSize){
    wrapper->hasEnded = 1;
    return base;
  }
  if(nextOffset == 12){
    ++(wrapper->structIndex);
    nextOffset = 0;
  }
  wrapper->baseOffset = nextOffset;
  return base;
}

DNAWrapper *makeDNAWrapper(BD *bases, unsigned int numBases){
  DNAWrapper *ret = (DNAWrapper*)malloc(sizeof(DNAWrapper));
  ret->bases = bases;
  ret->totalSize = numBases;
  ret->structIndex = 0;
  ret->baseOffset = 0;
  ret->hasEnded = (numBases == 0);
  return ret;
}

//Functions for using AAWrapper
char nextAcid(AAWrapper *wrapper){
  if(wrapper->hasEnded)
    return -1;
  AQ acidsStruct = wrapper->acids[wrapper->structIndex];
  char acid = getAAcid(acidsStruct, wrapper->baseOffset);
  unsigned int nextOffset = wrapper->baseOffset + 1;
  if(wrapper->structIndex * 4 + nextOffset >= wrapper-> totalSize){
    wrapper->hasEnded = 1;
    return acid;
  }
  if(nextOffset == 4){
    ++(wrapper->structIndex);
    nextOffset = 0;
  }
  wrapper->baseOffset = nextOffset;
  return acid;
}

AAWrapper *makeAAWrapper(AQ *acids, unsigned int numAcids){
  AAWrapper *ret = (AAWrapper*)malloc(sizeof(AAWrapper));
  ret->acids = acids;
  ret->totalSize = numAcids;
  ret->structIndex = 0;
  ret->baseOffset = 0;
  ret->hasEnded = (numAcids == 0);
  return ret;
}

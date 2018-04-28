#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "printing.h"

char baseChars[4] = {'A','T','C','G'};

char* acidStrings[24] = {
  "Ala-",
  "Arg-",
  "Asn-",
  "Asp-",
  "Cys-",
  "Gln-",
  "Glu-",
  "Gly-",
  "His-",
  "Ile-",
  "Leu-",
  "Lys-",
  "Met-",
  "Phe-",
  "Pro-",
  "Pyl-",
  "Sec-",
  "Ser-",
  "Thr-",
  "Trp-",
  "Tyr-",
  "Val-",
  "Ini-",
  "End-" 
};

char* baseToString(BD bases){
  char* ret = malloc(sizeof(char)*bases.size+1);
  int i;
  for(i=0; i<bases.size; ++i){
    ret[i] = baseChars[getBase(bases,i)];
  }
  ret[i] = '\0';
  return ret;
}

char* AAToString(AQ acids){
  char* ret = malloc(sizeof(char)*acids.size*4);
  int i;
  for(i=0; i<acids.size; ++i){    
    int pos = 4*i;
    strncpy(ret+(pos*sizeof(char)), acidStrings[getAAcid(acids,i)],((size_t)4));
  }
  ret[4*i-1] = '\0';
  return ret;
}

char* getNBases(DNAWrapper* wrapper, int n){
  char* ret = malloc(sizeof(char)*(n+1));
  
  unsigned int oldIndex = wrapper->structIndex;
  unsigned int oldOffset = wrapper->baseOffset;
  unsigned int oldEnded = wrapper->hasEnded;
  
  int base = nextBase(wrapper);
  int i;
  for(i = 0; i < n && base != -1; ++i){
    ret[i] = baseChars[base];
    base = nextBase(wrapper);
  }
  ret[i] = '\0';
  
  wrapper->structIndex = oldIndex;
  wrapper->baseOffset = oldOffset;
  wrapper->hasEnded = oldEnded;

  return ret;
}

char* getNAcids(AAWrapper* wrapper, int n){
  char* ret = malloc(sizeof(char)*(4*n));
  
  unsigned int oldIndex = wrapper->structIndex;
  unsigned int oldOffset = wrapper->baseOffset;
  unsigned int oldEnded = wrapper->hasEnded;
  
  int acid = nextAcid(wrapper);
  int i;
  for(i = 0; i < n && acid != -1; ++i){
    strncpy(ret+(4*i*sizeof(char)), acidStrings[acid], (size_t) 4);
    acid = nextAcid(wrapper);
  }
  ret[4*i] = '\0';
  
  wrapper->structIndex = oldIndex;
  wrapper->baseOffset = oldOffset;
  wrapper->hasEnded = oldEnded;
  
  return ret;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define A 0
#define T 1
#define C 2
#define G 3

#define Ala 0 
#define Arg 1
#define Asn 2
#define Asp 3
#define Cys 4
#define Gln 5
#define Glu 6
#define Gly 7
#define His 8
#define Ile 9
#define Leu 10
#define Lys 11
#define Met 12
#define Phe 13
#define Pro 14
#define Pyl 15
#define Sec 16
#define Ser 17
#define Thr 18
#define Trp 19
#define Tyr 20
#define Val 21
#define Ini 22
#define End 23

#define BD baseDodecuplet
#define AQ AAQuadruplet

// basic structures for internal representation
#ifndef STRUCT_DEF
#define STRUCT_DEF
typedef struct  {
  unsigned int size     :4;
  unsigned int bases    :24;
  unsigned int options  :4;
} baseDodecuplet;

typedef struct  {
  unsigned int size     :4;
  unsigned int acids    :20;
  unsigned int options  :8;
} AAQuadruplet;

typedef struct  {
  BD *bases;
  unsigned int totalSize;
  unsigned int structIndex;
  unsigned int baseOffset;
  unsigned char hasEnded;
} DNAWrapper;

typedef struct  {
  AQ *acids;
  unsigned int totalSize;
  unsigned int structIndex;
  unsigned int baseOffset;
  unsigned char hasEnded;
} AAWrapper;
#endif

int getBase(BD dodecuplet, int i);

int setBase(BD *dodecuplet, int i, unsigned int base);

int getAAcid(AQ quadruplet, int i);

//Functions for using DNAWrapper
char nextBase(DNAWrapper *wrapper);

DNAWrapper* makeDNAWrapper(BD *bases, unsigned int numBases);

//Functions for using AAWrapper
char nextAcid(AAWrapper *wrapper);

AAWrapper* makeAAWrapper(AQ *acids, unsigned int numAcids);

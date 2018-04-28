#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "structs.h"

char genCode[64] = {
  Phe,Leu,Leu,Phe,Tyr,End,Pyl,Tyr, //AAA AAT AAC AAG ATA ATT ATC ATG
  Cys,Sec,Trp,Cys,Ser,Ser,Ser,Ser, //ACA ACT ACC ACG AGA AGT AGC AGG
  Ile,Ile,Met,Ile,Asn,Lys,Lys,Asn, //TAA TAT TAC TAG TTA TTT TTC TTG
  Ser,Arg,Arg,Ser,Thr,Thr,Thr,Thr, //TCA TCT TCC TCG TGA TGT TGC TGG
  Val,Val,Val,Val,Asp,Glu,Glu,Asp, //CAA CAT CAC CAG CTA CTT CTC CTG
  Gly,Gly,Gly,Gly,Ala,Ala,Ala,Ala, //CCA CCT CCC CCG CGA CGT CGC CGG
  Leu,Leu,Leu,Leu,His,Gln,Gln,His, //GAA GAT GAC GAG GTA GTT GTC GTG
  Arg,Arg,Arg,Arg,Pro,Pro,Pro,Pro  //GCA GCT GCC GCG GGA GGT GGC GGG  
};


AQ transcript(BD bases){
  AQ acids;
  acids.size = (bases.size)/3;
  acids.options = 0;
  int i;
  unsigned int AAcids = 0;
  for(i = 0; i < acids.size; ++i){
    unsigned int B1 = getBase(bases, 3*i);
    unsigned int B2 = getBase(bases, 3*i+1);
    unsigned int B3 = getBase(bases, 3*i+2);
    unsigned int index = (B1 << 4) + (B2 << 2) + B3;
    unsigned int AAcid = (unsigned int) genCode[index];
    AAcids += AAcid << (i*5);
  }
  acids.acids = AAcids;
  return acids;
}

AAWrapper* transcriptWrapper(DNAWrapper* baseWrapper){
  
  int numAcids = baseWrapper->totalSize/3;
  int numBlocks = numAcids/4 + (numAcids%4 == 0 ? 0 : 1);
  
  AQ* blocks = (AQ*)malloc(sizeof(AQ)*numBlocks);
  int i;
  for(i = 0; i < numBlocks; ++i){
    blocks[i] = transcript((baseWrapper->bases)[i]);
  }
  
  return makeAAWrapper(blocks, numAcids);
}
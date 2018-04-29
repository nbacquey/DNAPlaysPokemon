#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "input.h"
#include "structs.h"
#include "transcript.h"

void testN(){
  BD test1;
  AQ testA;
  test1.size = 12;
  test1.options = 0;
  test1.bases = 0b011000110110101110010001;
  printf("%s\n",baseToString(test1));
  testA = transcript(test1);
  printf("%s\n",AAToString(testA));
  setBase(&test1, 2, A);
  printf("%s\n",baseToString(test1));
  testA = transcript(test1);
  printf("%s\n",AAToString(testA)); 
  
  BD test2 = test1;
  BD test3;
  
  test3.size = 5;
  test3.options = 0;
  test3.bases = 0b0111111011;
  
  BD* array = malloc(sizeof(BD)*3);
  array[0] = test1;
  array[1] = test2;
  array[2] = test3;
  
  DNAWrapper* wrapper1 = makeDNAWrapper(array,29);
  AAWrapper* wrapperA = transcriptWrapper(wrapper1);
  printf("%s\n",getNBases(wrapper1,34));
  printf("%s\n",getNAcids(wrapperA,34));
}

void testA(){

  char* DNA_sequence = "AAAAAAA\0";
  BD* genome_chunk;
  genome_chunk = newBD(DNA_sequence, 4);
  printf("================ %s\n",baseToString(*genome_chunk));

  struct genome g = build_genome();
  DNAWrapper* w = makeDNAWrapper(g.bds, g.num_base);
  printf("______num_base = %d : \n%s\n", g.num_base, getNBases(w, g.num_base));


  printf("\n\n\n\n\n\n\n\nççççççççççççççççççççççççç\n");

}

int main (int argc, char **argv){


  testA();

  testN();
  return 0;
  
}
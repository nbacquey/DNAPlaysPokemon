#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "input.h"
#include "printing.h"
#include "structs.h"
#include "transcript.h"
#include "frequency.h"
#include "keyHandler.h"
#include "VBAInterface.h"

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
  printf("%s\n",getNBases(wrapper1,40));
  printf("%s\n",getNAcids(wrapperA,34));
  
  occurencyMapper *mapper = countNGrams(wrapper1, 4);
  
  printOccurencies(mapper);
}

void testA(){


  genome * g = build_genome();

  // test get next button :
  int btn;
  btn = get_next_btn_2B(g-> wrappers[0]);
  printf("%d\n", btn);
  btn = get_next_btn_2B(g-> wrappers[0]);
  printf("%d\n", btn);
  //-------------

  occurencyMapper** mappers = mapGenome(g, 6);
  int i;
  for(i = 0; i < g->num_wrappers; ++i){
    printOccurencies(mappers[i]);
  }

}

int main(int argc, char **argv){


  //testA();

  //testN();


  genome * g = build_genome();
  int next_btn;

  for (int idx_wrapper = 0; idx_wrapper < g->num_wrappers; ++idx_wrapper){
    DNAWrapper* current_w = g->wrappers[idx_wrapper];
    while( (next_btn = get_next_btn_3B(current_w)) != -1){
      sendCommand(next_btn);
      usleep(100000/(THROTTLE/100));
    }
  }
  
  return 0;
  
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "printing.h"


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


void transcript(BD bases, AQ *acids){
  acids->size = (bases.size)/3;
  int i;
  unsigned int AAcids = 0;
  for(i = 0; i < acids->size; ++i){
    unsigned int B1 = getBase(bases, 3*i);
    unsigned int B2 = getBase(bases, 3*i+1);
    unsigned int B3 = getBase(bases, 3*i+2);
    unsigned int index = (B1 << 4) + (B2 << 2) + B3;
    unsigned int AAcid = (unsigned int) genCode[index];
    AAcids += AAcid << (i*5);
  }
  acids->acids = AAcids;
  return;
}



void testN(){
  BD test1;
  AQ testA;
  test1.size = 12;
  test1.options = 0;
  test1.bases = 0b011000110110101110010001;
  printf("%s\n",baseToString(test1));
  transcript(test1, &testA);
  printf("%s\n",AAToString(testA));
  setBase(&test1, 2, A);
  printf("%s\n",baseToString(test1));
  transcript(test1, &testA);
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
  
  DNAWrapper* wrapper = makeDNAWrapper(array,29);
  char c;
  while( (c = nextBase(wrapper)) != -1){
    printf("%d\n",c);
  }
}


  
int build_genome(){

  FILE * fasta_file;
  fasta_file = fopen("data/line-per-line.txt", "r");
  if (NULL == fasta_file){
    perror("opening file");
    return (-1);
  }

  int c; // getc will send a char as an int
  int num_base = 0; // number of DNA base that have been parsed

  char DNAsequence_chunk[12 + 1] = "            \0"; // the chunk that will fill a BD struct
  // +1 for the string end

  while((c = getc(fasta_file)) != -1) {
    printf("read char: %c\n", c);
    if (c == '>') {
      printf("this is a >, thus I skip : \n");
      // Skip until the next newline:
      do {
        c = getc(fasta_file);
        printf("%c-", c);
      } while (c != -1 && c != '\n');
      continue;
    }else if (c == 65 || c == 84 ||c == 67 || c == 71){
      // base character A, T, C, or G

      if (num_base%12 == 0){
        printf("DNAsequence_chunk if full : %s. chunk num : %i\n", DNAsequence_chunk, num_base/12);
      }

      printf("to keep : %c\n", c);
      printf("%i mod %i = %d \n", num_base, 12, num_base % 12 );
      DNAsequence_chunk[num_base % 12]=c;
      num_base+=1; // this is a correct base

    }else{
      printf("%c is not a charactere for a base, thus I skip it \n", c);
      continue;
    }
  }

  fclose(fasta_file);

  return 0;

}


BD* newBD(char* DNA_sequence){
  BD* genome_chunk = malloc (sizeof (BD));

  genome_chunk->size = strlen(DNA_sequence);
  genome_chunk->options = 0;

  for (int i = 0; i < strlen(DNA_sequence); ++i){
    printf("%d", i);
    if (DNA_sequence[i] == 65){
      setBase(genome_chunk, i, A);
    }else if(DNA_sequence[i] == 84){
      setBase(genome_chunk, i, T);
    }else if(DNA_sequence[i] == 67){
      setBase(genome_chunk, i, C);
    }else if(DNA_sequence[i] == 71){
      setBase(genome_chunk, i, G);
    }
  }
  return genome_chunk;
}


void testA(){

  char* DNA_sequence = "AAAAAAA\0";
  BD* genome_chunk;
  genome_chunk = newBD(DNA_sequence);
  printf("================ %s\n",baseToString(*genome_chunk));

  build_genome();

}

int main (int argc, char **argv){


  testA();

  testN();
  return 0;
  
}
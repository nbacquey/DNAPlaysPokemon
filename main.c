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

typedef struct baseDodecuplet {
  unsigned int size     :4;
  unsigned int bases    :24;
  unsigned int options  :4;
} baseDodecuplet;

typedef struct AAQuadruplet {
  unsigned int size     :4;
  unsigned int acids    :20;
  unsigned int options  :8;
} AAQuadruplet;

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

char* baseToString(BD bases){
  char* ret = malloc(sizeof(char)*bases.size);
  int i;
  for(i=0; i<bases.size; ++i){
    switch (getBase(bases,i)){
      case A:
        ret[i] = 'A';
        break;
      case T:
        ret[i] = 'T';
        break;
      case C:
        ret[i] = 'C';
        break;
      case G:
        ret[i] = 'G';
        break;
      default:
        break;
    }
  }
  return ret;
}

char* AAToString(AQ acids){
  char* ret = malloc(sizeof(char)*acids.size*4);
  int i;
  for(i=0; i<acids.size; ++i){
    int pos = 4*i;
    switch (getAAcid(acids,i)){
      case Ala:
        strncpy(ret+(pos*sizeof(char)), "Ala-",((size_t)4));
        break;
      case Arg:
        strncpy(ret+(pos*sizeof(char)), "Arg-",((size_t)4));
        break;
      case Asn:
        strncpy(ret+(pos*sizeof(char)), "Asn-",((size_t)4));
        break;
      case Asp:
        strncpy(ret+(pos*sizeof(char)), "Asp-",((size_t)4));
        break;
      case Cys:
        strncpy(ret+(pos*sizeof(char)), "Cys-",((size_t)4));
        break;
      case Gln:
        strncpy(ret+(pos*sizeof(char)), "Gln-",((size_t)4));
        break;
      case Glu:
        strncpy(ret+(pos*sizeof(char)), "Glu-",((size_t)4));
        break;
      case Gly:
        strncpy(ret+(pos*sizeof(char)), "Gly-",((size_t)4));
        break;
      case His:
        strncpy(ret+(pos*sizeof(char)), "His-",((size_t)4));
        break;
      case Ile:
        strncpy(ret+(pos*sizeof(char)), "Ile-",((size_t)4));
        break;
      case Leu:
        strncpy(ret+(pos*sizeof(char)), "Leu-",((size_t)4));
        break;
      case Lys:
        strncpy(ret+(pos*sizeof(char)), "Lys-",((size_t)4));
        break;
      case Met:
        strncpy(ret+(pos*sizeof(char)), "Met-",((size_t)4));
        break;
      case Phe:
        strncpy(ret+(pos*sizeof(char)), "Phe-",((size_t)4));
        break;
      case Pro:
        strncpy(ret+(pos*sizeof(char)), "Pro-",((size_t)4));
        break;
      case Pyl:
        strncpy(ret+(pos*sizeof(char)), "Pyl-",((size_t)4));
        break;
      case Sec:
        strncpy(ret+(pos*sizeof(char)), "Sec-",((size_t)4));
        break;
      case Ser:
        strncpy(ret+(pos*sizeof(char)), "Ser-",((size_t)4));
        break;
      case Thr:
        strncpy(ret+(pos*sizeof(char)), "Thr-",((size_t)4));
        break;
      case Trp:
        strncpy(ret+(pos*sizeof(char)), "Trp-",((size_t)4));
        break;
      case Tyr:
        strncpy(ret+(pos*sizeof(char)), "Tyr-",((size_t)4));
        break;
      case Ini:
        strncpy(ret+(pos*sizeof(char)), "Ini-",((size_t)4));
        break;
      case End:
        strncpy(ret+(pos*sizeof(char)), "End-",((size_t)4));
        break;
      default:
        break;
    }
  }
  ret[4*i-1] = '\0';
  return ret;
}


void testN(){
  BD test;
  AQ test2;
  test.size = 12;
  test.options = 0;
  test.bases = 0b011000110110101110010001;
  printf("%s\n",baseToString(test));
  transcript(test, &test2);
  printf("%s\n",AAToString(test2));
  setBase(&test, 2, A);
  printf("%s\n",baseToString(test));
  transcript(test, &test2);
  printf("%s\n",AAToString(test2)); 
}


  
int build_genome(){

  FILE * fasta_file;
  fasta_file = fopen("data/line-per-line.txt", "r");
  if (NULL == fasta_file){
    perror("opening file");
    return (-1);
  }

  int c; // getc will send a char as an int
  while((c = getc(fasta_file)) != -1) {
    printf("read char: %c\n", c);
    if (c == '\n') {
      printf("this is a carriage return, thus I skip it \n");
      continue;
    }else if (c == '>') {
      printf("this is a >, thus I skip : \n");
      // Skip until the next newline:
      do {
        c = getc(fasta_file);
        printf("%c-", c);
      } while (c != -1 && c != '\n');
      continue;
    }else {
      printf("to keep : %c\n", c);
    }
  }

  fclose(fasta_file);

  return 0;

}

void testA(){

  build_genome();

}

int main (int argc, char **argv){


  testA();

  testN();
  return 0;
  
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define A 0
#define T 1
#define C 2
#define G 3

#define BD baseDodecuplet
#define AQ AAQuadruplet

typedef struct baseDodecuplet {
  unsigned int size     :4;
  unsigned int bases    :24;
  unsigned int options  :4;
} baseDodecuplet;

typedef struct AAQuadruplet {
  unsigned int size     :2;
  unsigned int acids    :20;
  unsigned int options  :10;
} AAQuadruplet;

int getBase(BD dodecuplet, int i){
  if(i >= dodecuplet.size)
    return -1;
  return (dodecuplet.bases >> (2*i)) & 0b11 ;
}

int getAAcid(AQ quadruplet, int i){
  if(i >= quadruplet.size)
    return -1;
  return (quadruplet.acids >> (5*i)) & 0b11111 ;
}

int main (int argc, char **argv){
  BD test;
  test.size = 6;
  test.options = 0;
  test.bases = 0b011000110110;
  printf("Enumération des bases %d %d %d %d %d %d\n",getBase(test,0),getBase(test,1),getBase(test,2),getBase(test,3),getBase(test,4),getBase(test,6));



  FILE * fasta_file;
  char line[80];

  fasta_file = fopen("data/line-per-line.txt", "r");
  if (NULL == fasta_file){
    perror("opening file");
    return (-1);
  }

  while (EOF != fscanf(fasta_file, " %[^\n]", line)){
    // matches characters until a newline is encountered
    // the newline character is left behind in the input stream.
    printf("> %s\n", line);
  }

  fclose(fasta_file);

  return 0;
  
}
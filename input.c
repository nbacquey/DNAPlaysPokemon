#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "input.h"

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

  BD * genome ;
  genome = malloc(0 * sizeof(BD));


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
        int num_chunk = num_base/12;
        printf("DNAsequence_chunk if full : %s. chunk num : %i\n", DNAsequence_chunk, num_chunk);
        BD* genome_chunk;
        genome_chunk = newBD(DNAsequence_chunk);
        printf("================ %s\n",baseToString(*genome_chunk));
        genome = realloc(genome, num_chunk + 1 * sizeof(BD));
        genome[num_chunk] = *genome_chunk;
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

  // End of the file

  // possibly some base left :
  if (num_base%12 != 0){
    DNAsequence_chunk[num_base % 12   +1]='\0';
    int num_chunk = num_base/12;
    printf("%i mod %i = %d \n", num_base, 12, num_base % 12 );

    BD* genome_chunk;
    genome_chunk = newBD(DNAsequence_chunk);
    printf("================ %s\n",baseToString(*genome_chunk));
    genome = realloc(genome, num_chunk + 1 * sizeof(BD));
    genome[num_chunk] = *genome_chunk;

  }

  fclose(fasta_file);
  free(genome);

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


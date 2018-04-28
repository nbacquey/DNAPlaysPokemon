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

      num_base+=1; // this is a correct base

      printf("to keep : %c, --- %d ---, its index = %d \n", c, num_base -1 , (num_base -1) % 12);
      printf("%i mod %i = %d \n", num_base, 12, num_base % 12 );
      DNAsequence_chunk[(num_base-1) % 12]=c;
      //                          A
      //                          |___ because indexing begin to 0

      if (num_base%12 == 0){
        int num_chunk = num_base/12;
        printf("DNAsequence_chunk if full : %s. chunk num : %i\n", DNAsequence_chunk, num_chunk);
        BD* genome_chunk;
        genome_chunk = newBD(DNAsequence_chunk, 12);
        printf("================ %s\n",baseToString(*genome_chunk));
        genome = realloc(genome, num_chunk * sizeof(BD));
        genome[num_chunk-1] = *genome_chunk;

        DNAWrapper* w = makeDNAWrapper(genome, num_base);
        printf("????num_base = %d : \n%s\n", num_base, getNBases(w, num_base));
      }


    }else{
      printf("%c is not a charactere for a base, thus I skip it \n", c);
      continue;
    }
  }

  // End of the file

  // possibly some base left :
  if (num_base%12 != 0){


    DNAsequence_chunk[num_base % 12 ]='\0';
    printf("AT THE END OF THE FILE : DNAsequence_chunk = %s, its len = %d\n", DNAsequence_chunk, num_base % 12 );
    
    int num_chunk = num_base/12;
    printf("%i mod %i = %d \n", num_base, 12, num_base % 12 );

    BD* genome_chunk;
    genome_chunk = newBD(DNAsequence_chunk, num_base%12);
    printf("================ %s\n",baseToString(*genome_chunk));
    genome = realloc(genome, num_chunk * sizeof(BD));
    genome[num_chunk] = *genome_chunk;

  }

  DNAWrapper* w = makeDNAWrapper(genome, num_base);
  printf("!!!!!!num_base = %d : \n%s\n", num_base, getNBases(w, num_base));



  fclose(fasta_file);
  free(genome);

  return 0;

}


BD* newBD(char* DNA_sequence, int len){
  BD* genome_chunk = malloc (sizeof (BD));

  genome_chunk->size = len;
  genome_chunk->options = 0;

  printf("in newBD : string %s and its len is %d \n", DNA_sequence, len);

  for (int i = 0; i < len; ++i){
    printf("%d, ", i);
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


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "input.h"



void parse_fasta(struct genome* g, char * path){
 

  FILE * fasta_file;
  fasta_file = fopen(path, "r");
  if (NULL == fasta_file){
    perror("opening file");
  }

  int c; // getc will send a char as an int
  int num_chunk = g->num_base / 12; 

  char DNAsequence_chunk[12 + 1] = "            \0"; // the chunk that will fill a BD struct
  // +1 for the string end
  // TODO : use last genome.bds.sequence


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

      g->num_base+=1; // this is a correct base

      printf("to keep : %c, --- %d ---, its index = %d, its num_chunk = %d \n", c, g->num_base -1 , (g->num_base -1) % 12, num_chunk);
      printf("%i mod %i = %d \n", g->num_base, 12, g->num_base % 12 );
      DNAsequence_chunk[(g->num_base-1) % 12]=c;
      //                             A
      //                             |___ because indexing begin to 0

      if (g->num_base%12 == 0){
        num_chunk += 1;
        printf("DNAsequence_chunk if full : %s. chunk num : %i\n", DNAsequence_chunk, num_chunk);
        BD* genome_chunk;
        genome_chunk = newBD(DNAsequence_chunk, 12);
        printf("================ %s\n",baseToString(*genome_chunk));
        g->bds = realloc(g->bds, num_chunk * sizeof(BD));
        g->bds[num_chunk-1] = *genome_chunk;

        DNAWrapper* w = makeDNAWrapper(g->bds, g->num_base);
        printf("????g->num_base = %d : \n%s\n", g->num_base, getNBases(w, g->num_base));
      }


    }else{
      printf("%c is not a charactere for a base, thus I skip it \n", c);
      continue;
    }
  }

  // End of the file


  // possibly some base left :
  if (g->num_base%12 != 0){
    num_chunk += 1 ; 

    DNAsequence_chunk[g->num_base % 12 ]='\0';
    printf("AT THE END OF THE FILE :DNAsequence_chunk = %s, its len = %d, its num_chunk = %d\n", DNAsequence_chunk, g->num_base % 12, num_chunk );
      
    DNAWrapper* w = makeDNAWrapper(g->bds, g->num_base);
    printf("!!!!!!num_base = %d : \n%s\n", g->num_base, getNBases(w, g->num_base));

    BD* genome_chunk;
    genome_chunk = newBD(DNAsequence_chunk, (g->num_base+1)%12);
    printf("================ %s\n",baseToString(*genome_chunk));
    printf("we realloc\n");
    g->bds = realloc(g->bds, num_chunk  * sizeof(BD));
    printf("we write it\n");
    g->bds[num_chunk-1] = *genome_chunk;
    printf("end write\n");

  }



  DNAWrapper* w = makeDNAWrapper(g->bds, g->num_base);
  printf("ooooooo!!!!!!num_base = %d : \n%s\n", g->num_base, getNBases(w, g->num_base));



  fclose(fasta_file);


}

struct genome build_genome(){

  struct genome g ; 
  g.bds = NULL ;
  g.num_base = 0 ; 

  char* dirpath = "data/fasta"; 
  DIR *d = opendir(dirpath);
  if (d==NULL){ // couldn't open directory
    perror("opening dir");
  return g;
  }


  struct dirent *dir;
  while ((dir = readdir(d)) != NULL) { // readdir send NULL if no more file to read
    printf("%s\n", dir->d_name);
    if ( fnmatch( "Homo_sapiens.GRCh38.dna.chromosome.*.fa.gz" , dir->d_name , 0) == 0 ){
      printf("XXXX : %s\n", dir->d_name);


      char filepath[strlen(dirpath) + strlen(dir->d_name) +1 ] ; 
      int size_filepath = sprintf(filepath, "%s/%s",dirpath,dir->d_name);
      printf("%s\n", filepath);


      char cmd[10 + 1 + size_filepath + 1]  ;  // "gunzip" + ' ' + gzfilepath + '\0'
      strcpy( cmd, "gunzip -k " );
      strcat( cmd, filepath);
      printf("%s\n", cmd);
      int status = system( cmd );


      filepath[strlen(filepath)-3]=0 ; // - 3 = .gz  `\0
      printf("filepath = %s \n", filepath);
      parse_fasta(&g, filepath);
      DNAWrapper* w = makeDNAWrapper(g.bds, g.num_base);
      printf("______num_base = %d : \n%s\n", g.num_base, getNBases(w, g.num_base));


    }
  }
  closedir(d);


  printf("////////////////////////////\n");

  return g;

}


BD* newBD(char* DNA_sequence, int len){
  BD* genome_chunk = malloc (sizeof (BD));

  genome_chunk->size = len + 1;
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


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "input.h"
#include "printing.h"



DNAWrapper* parse_fasta(char * path){
 
  printf("\nParsing started from %s...\n",path);

  FILE * fasta_file;
  fasta_file = fopen(path, "r");
  if (NULL == fasta_file){
    perror("opening file");
  }

  int c; // getc will send a char as an int
  unsigned int num_base = 0 ; // number of base that have been read.
  unsigned int num_chunk = 0; 

  unsigned int allocated = 1024; // must be divisabe by 2
  BD* bds = malloc(allocated * sizeof(BD));

  char DNAsequence_chunk[12 + 1] = "            \0"; // the chunk that will fill a BD struct
  // +1 for the string end

  while((c = getc(fasta_file)) != -1) {
    //printf("read char: %c\n", c);
    if (c == '>') {
      //printf("this is a >, thus I skip : \n");
      // Skip until the next newline:
      do {
        c = getc(fasta_file);
        //printf("%c-", c);
      } while (c != -1 && c != '\n');
      continue;
    }else if (c == 'A' || c == 'T' ||c == 'C' || c == 'G'){
      // base character A, T, C, or G

      num_base+=1; // this is a correct base
      
      if(num_base % 10000000 == 0){
        printf("\r%d Mbases parsed...", num_base/1000000);
        fflush(stdout);
      }

      //printf("to keep : %c, --- %d ---, its index = %d, its num_chunk = %d \n", c, num_base -1 , (num_base -1) % 12, num_chunk);
      //printf("%i mod %i = %d \n", num_base, 12, num_base % 12 );
      DNAsequence_chunk[(num_base-1) % 12]=c;
      //                          A
      //                          |___ because indexing begin to 0

      if (num_base%12 == 0){
        num_chunk += 1;
        //printf("DNAsequence_chunk if full : %s. chunk num : %i\n", DNAsequence_chunk, num_chunk);
        BD* genome_chunk;
        genome_chunk = newBD(DNAsequence_chunk, 12);
        //printf("================ %s\n",baseToString(*genome_chunk));
        bds[num_chunk-1] = *genome_chunk;

        //DNAWrapper* w = makeDNAWrapper(bds, num_base);
        //printf("????num_base = %d : \n%s\n", num_base, getNBases(w, num_base));


        if (num_chunk == allocated){
          allocated = 3 * allocated / 2; // think that it must be integer all along
          bds = realloc(bds, allocated * sizeof(BD));
          // allocated + 1/2 * allocated 
          // = 3 / 2 allocated
        }
      }


    }else{
      //printf("%c is not a charactere for a base, thus I skip it \n", c);
      continue;
    }
  }

  // End of the file


  // possibly some base left :
  if (num_base%12 != 0){
    num_chunk += 1 ; 

    DNAsequence_chunk[num_base % 12 ]='\0';
    //printf("AT THE END OF THE FILE :DNAsequence_chunk = %s, its len = %d, its num_chunk = %d\n", DNAsequence_chunk, num_base % 12, num_chunk );
      
    //DNAWrapper* w = makeDNAWrapper(bds, num_base);
    //printf("!!!!!!num_base = %d : \n%s\n", num_base, getNBases(w, num_base));

    BD* genome_chunk;
    genome_chunk = newBD(DNAsequence_chunk, (num_base+1)%12);
    //printf("================ %s\n",baseToString(*genome_chunk));
    //printf("we realloc\n");
    bds = realloc(bds, num_chunk  * sizeof(BD));
    //printf("we write it\n");
    bds[num_chunk-1] = *genome_chunk;
    //printf("end write\n");

  }

  // possibly too much allocated space :
  if (num_chunk != allocated){
    bds = realloc(bds, num_chunk * sizeof(BD));
  }



  DNAWrapper* w = makeDNAWrapper(bds, num_base);
  //printf("ooooooo!!!!!!num_base = %d : \n%s\n", num_base, getNBases(w, num_base));

  printf("\nParsed %d bases from file : %s\nSample: %s...%s\n\n", num_base, path, getNBasesFrom(w,20,0), getNBasesFrom(w,20,(num_base)-20));

  fclose(fasta_file);

  return w;


}

genome * build_genome(){

  genome * g; 
  g = malloc(sizeof(genome));

  char* dirpath = "data/fasta"; 
  DIR *d = opendir(dirpath);
  if (d==NULL){ // couldn't open directory
    perror("opening dir");
    return g;
  }


  struct dirent *dir;


  DNAWrapper** ws = malloc(0 * sizeof(DNAWrapper*)); // point to list of wrapper (one per fasta file)
  unsigned int num_wrappers = 0 ; // number of file that havve been parsed

  while ((dir = readdir(d)) != NULL) { // readdir send NULL if no more file to read
    //printf("%s\n", dir->d_name);
    if ( fnmatch( "Homo_sapiens.GRCh38.dna.chromosome.*.fa" , dir->d_name , 0) == 0 ){
      //printf("XXXX : %s\n", dir->d_name);

      num_wrappers += 1 ;

      char filepath[strlen(dirpath) + strlen(dir->d_name) +1 ] ; 
      sprintf(filepath, "%s/%s",dirpath,dir->d_name);
      //printf("filepath = %s \n", filepath);

      DNAWrapper* current_wrapper = parse_fasta(filepath);
      char* filename = malloc(sizeof(char)*256);
      current_wrapper->filePath = strncpy(filename, dir->d_name, 256);
      filename[255] = '\0';
      //printf("&&&&&&&&&&&&&&&\nnum_wrapper = %d, num_base = %d : \n%s\n", num_wrappers, current_wrapper->totalSize, getNBases(current_wrapper, current_wrapper->totalSize));

      ws = realloc(ws, num_wrappers * sizeof(DNAWrapper*));
      ws[num_wrappers-1] = current_wrapper;

    }
  }
  closedir(d);


  printf("\n====All files parsed====\n");
 
  g->wrappers = ws ;
  g->num_wrappers = num_wrappers ; 

  return g;

}


BD* newBD(char* DNA_sequence, unsigned int len){
  BD* genome_chunk = malloc (sizeof (BD));

  genome_chunk->size = len + 1;
  genome_chunk->options = 0;

  //printf("in newBD : string %s and its len is %d \n", DNA_sequence, len);

  for (unsigned int i = 0; i < len; ++i){
    //printf("%d, ", i);
    if (DNA_sequence[i] == 'A'){
      setBase(genome_chunk, i, A);
    }else if(DNA_sequence[i] == 'T'){
      setBase(genome_chunk, i, T);
    }else if(DNA_sequence[i] == 'C'){
      setBase(genome_chunk, i, C);
    }else if(DNA_sequence[i] == 'G'){
      setBase(genome_chunk, i, G);
    }
  }
  return genome_chunk;
}


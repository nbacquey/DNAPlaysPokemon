#include <dirent.h> 
#include <fnmatch.h>

#include "structs.h"



struct genome
{
  BD* bds;
  int num_base; // number of DNA base that have been parsed
};



// prototypes :
void parse_fasta(struct genome * g, char * path);
struct genome build_genome();
BD* newBD(char* DNA_sequence, int len);

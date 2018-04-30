#include <dirent.h> 
#include <fnmatch.h>

#include "structs.h"



struct genome
{
  DNAWrapper** wrappers;
  int num_wrappers; // number of fasta file that have been parsed
};



// prototypes :
DNAWrapper* parse_fasta(char * path);
struct genome * build_genome();
BD* newBD(char* DNA_sequence, unsigned int len);

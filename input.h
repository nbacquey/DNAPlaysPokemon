#include <dirent.h> 
#include <fnmatch.h>

#include "structs.h"


// prototypes :
DNAWrapper* parse_fasta(char * path);
genome * build_genome();
BD* newBD(char* DNA_sequence, unsigned int len);

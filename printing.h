#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "structs.h"
#include "frequency.h"

char* baseToString(BD bases);

char* AAToString(AQ acids);

char* getNBases(DNAWrapper* wrapper, int n);
char* getNBasesFrom(DNAWrapper* wrapper, int n, int start);

char* getNAcids(AAWrapper* wrapper, int n);
char* getNAcidsFrom(AAWrapper* wrapper, int n, int start);

void printOccurencies(occurencyMapper *mapper);


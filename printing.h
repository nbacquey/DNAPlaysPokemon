#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "structs.h"

char* baseToString(BD bases);

char* AAToString(AQ acids);

char* getNBases(DNAWrapper* wrapper, int n);

char* getNAcids(AAWrapper* wrapper, int n);


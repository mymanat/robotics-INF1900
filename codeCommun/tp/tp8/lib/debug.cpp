#include "memoire.h"
#include <string.h>

void printVaraibleEtat(char variableEtat[])
{
    initialisationUART8Bits1StopBitNoneParity();
    transmettreChainePc(variableEtat, strlen(variableEtat), 10);
}

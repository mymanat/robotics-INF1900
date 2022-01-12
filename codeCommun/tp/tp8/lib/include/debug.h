#pragma once

// #define DEBUG_PRINT(variableEtat) printVaraibleEtat(variableEtat)

// #define DEBUG   // À commenter au besoin

#ifdef DEBUG

# define DEBUG_PRINT(x) printVaraibleEtat (x) // ou par RS-232

#else

# define DEBUG_PRINT(x) do {} while (0) // code mort

#endif
void printVaraibleEtat(char variableEtat[]);
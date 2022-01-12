#pragma once
#define F_CPU 8000000
#include <avr/io.h>
bool estDebutProgramme(uint8_t instruction);
void attendre25MsFois(uint8_t operande);
void allumerDelInstruction(uint8_t operande, volatile uint8_t &port);
void eteindreDelInstruction(volatile uint8_t &port);
void allumerMatriceDelAffichage(uint8_t operande, volatile uint8_t &port);
void eteindreMatriceDelAffichage(volatile uint8_t &port);


#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "del.h"
#include "memoire.h"

#define DBT 0x01
#define FIN 0xFF
#define DELAIS 25
#define VERT 0x1
#define ROUGE 0x2
#define ETEINT 0x0

bool estDebutProgramme(uint8_t instruction)
{
    if (instruction == DBT)
    {
        return true;
    }
    else
        return false;
}

void attendre25MsFois(uint8_t operande)
{
    for (uint16_t i = 0; i < operande; i++)
    {
        _delay_ms(DELAIS);
    }
}

void allumerDelInstruction(uint8_t operande, volatile uint8_t &port)
{
    if (operande <= 127)
        allumerDel(VERT, port);
    else
        allumerDel(ROUGE, port);
}

void eteindreDelInstruction(volatile uint8_t &port)
{
    allumerDel(ETEINT, port);
}

void allumerMatriceDelAffichage(uint8_t operande, volatile uint8_t &port)
{
    port = operande;
}

void eteindreMatriceDelAffichage(volatile uint8_t &port)
{
    port = ETEINT;
}

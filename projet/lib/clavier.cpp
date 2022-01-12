#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "memoire.h"

#define BOUTON_C2_APPUYE (PINC & (1 << PC2))
#define BOUTON_C3_APPUYE (PINC & (1 << PC3))
#define BOUTON_C4_APPUYE (PINC & (1 << PC4))
#define BOUTON_C5_APPUYE (PINC & (1 << PC5))
#define BOUTON_C6_APPUYE (PINC & (1 << PC6))
#define BOUTON_C7_APPUYE (PINC & (1 << PC7))

void initialisationInterruptPCINT2()
{
    cli();
    // Pin Change Interrupt Enable 2 pour PCINT 23:16
    PCICR |= (1 << PCIE2);
    // Active les interruptions pour PCINT 23:18
    PCMSK2 |= (1 << PCINT23) | (1 << PCINT22) | (1 << PCINT21) | (1 << PCINT20) | (1 << PCINT19) | (1 << PCINT18);
    // Prêt à recevoir des interruptions
    sei();
}

void initialisationPD7aPD5Output()
{
    DDRC |= 1 << PC7 | 1 << PC6 | 1 << PC5;
    DDRC &= ~(1 << PC4) & ~(1 << PC3) & ~(1 << PC2);
    PORTC |= 1 << PC7 | 1 << PC6 | 1 << PC5;
    PORTC &= ~(1 << PC4) & ~(1 << PC3) & ~(1 << PC2);
}

void initialisationPD4aPD2Output()
{
    DDRC |= 1 << PC4 | 1 << PC3 | 1 << PC2;
    DDRC &= ~(1 << PC7) & ~(1 << PC6) & ~(1 << PC5);
    PORTC |= 1 << PC4 | 1 << PC3 | 1 << PC2;
    PORTC &= ~(1 << PC7) & ~(1 << PC6) & ~(1 << PC5);
}

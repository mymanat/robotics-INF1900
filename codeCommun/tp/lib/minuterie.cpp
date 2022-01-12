#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void initialisationMinuterie1(void)
{
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontroleur n'est pas prêt...
    cli();
    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0);
    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1 << ISC11) | (1 << ISC10);
    // sei permet de recevoir à nouveau des interruptions.
    sei();
}

void partirMinuterieTimer1ModeCTCPrescaler1024(uint16_t duree)
{
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    TCNT1 = 0;
    OCR1A = duree;
    // WGM11 et WGM10 sont a 0 par defaut donc pas utile
    TCCR1A = 0;
    // Mode = CTC, Prescaler = 1024
    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
    TCCR1C = 0;
    // Input Capture Interrupt Enable
    TIMSK1 |= (1 << OCIE1A);
}

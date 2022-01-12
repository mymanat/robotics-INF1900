

#include <avr/io.h>
#define F_CPU 8000000

void ajustementPWM(uint16_t duree, uint16_t pourcentage)
{
    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5
    // page 130 de la description technique du ATmega324PA)
    OCR1A = duree * pourcentage;
    OCR1B = duree;
    // division d'horloge par 8 - implique une frequence de PWM fixe
    TCCR1A = (1 << WGM10);
    TCCR1B = (1 << CS11);
    TCCR1C = 0;
}

int main()
{
    DDRD = 0xff;
    PORTD = 1;
    // ajustementPWM(100, 100);
    return 0;
}
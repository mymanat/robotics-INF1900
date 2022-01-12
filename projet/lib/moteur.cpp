#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include "can.h"

#define SORTIE 0xff
#define VERT 0x01
#define ROUGE 0x02
#define DELAIS 10
#define VINGTCINQPOURC 64
#define CINQUENTEPOURC 128
#define SOIXANTEQUINZEPOURC 191

void ajustementPWMmateriellePhaseCorrecte8Bits(uint16_t pourcentage1, uint16_t pourcentage2)
{
    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5
    // page 130 de la description technique du ATmega324PA)

    OCR1A = pourcentage1;
    OCR1B = pourcentage2;
    // division d'horloge par 8 - implique une frequence de PWM fixe

    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B = (1 << ICES1) | (1 << CS11);
    TCCR1C = 0;
}

void ajustementPWMPourcentage(uint16_t pourcentage1, uint16_t pourcentage2)
{
    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5
    // page 130 de la description technique du ATmega324PA)

    OCR1A = (pourcentage1 * 255 / 100);
    OCR1B = (pourcentage2 * 255 / 100);

    if ((pourcentage1 * 255 / 100) == 255)
        OCR1A = 254;
    if ((pourcentage2 * 255 / 100) == 255)
        OCR1B = 254;

    // division d'horloge par 8 - implique une frequence de PWM fixe
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B = (1 << ICES1) | (1 << CS11);
    TCCR1C = 0;
}

void changerVitesseAvecLuminosite(uint8_t lumBasse, uint8_t lumAmbiante)
{
    uint16_t lecture; // --> 0 à 255
    can convertir = can();

    lecture = convertir.lecture(0) >> 2; // lecture --> entre 0 et 255

    // L'intensité lumineuse est basse, la lumière est donc verte
    if (lecture < lumBasse)
        ajustementPWMmateriellePhaseCorrecte8Bits(VINGTCINQPOURC, VINGTCINQPOURC); //25%

    // L'intensité lumineuse est moyenne(lumière ambiante) (plus grande que la lumière basse, mais plus petite
    //que le seuil maximal pour être considéré ambiant),la lumière est donc ambré
    if ((lecture >= lumBasse) && (lecture < lumAmbiante))
    {
        ajustementPWMmateriellePhaseCorrecte8Bits(CINQUENTEPOURC, CINQUENTEPOURC); //50%
    }

    // L'intensité lumineuse est forte, la lumière est donc rouge
    if (lecture >= lumAmbiante)
        ajustementPWMmateriellePhaseCorrecte8Bits(SOIXANTEQUINZEPOURC, SOIXANTEQUINZEPOURC); //75%
}

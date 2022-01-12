///////////////////////////////////////////////////////////////
//Machine à états de Moore contrôlant l'allumage d'une LED
//Date : 29/01/2021
//Auteur : Ivan Ivanov et Eliott Schuhmacher-Wantz
//Matricules : 2087256 et 2081542
//Groupe 151
///////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//État présent   Entrée D2    D3    État suivant     Sortie D
//INIT                  1     X           E1           ETEINT
//INIT                  X     1           INIT         ETEINT
//E1                    1     X           E2           ROUGE
//E1                    X     1           E3           ROUGE
//E2                    1     X           INIT         VERT
//E2                    X     1           INIT         VERT
//E3                    X     1           E2           ETEINT
//E3                    X     1           E4           ETEINT
///////////////////////////////////////////////////////////////

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;
const uint16_t  DUREE= 10000;
const uint16_t SECONDE = 10000;

ISR(TIMER1_COMPA_vect)
{
    minuterieExpiree = 1;
}

ISR(INT0_vect)
{
    boutonPoussoir = 1;
    // anti-rebond
    _delay_ms(30);
    EIFR |= (1 << INTF0);
}

void partirMinuterie(uint16_t duree)
{
    minuterieExpiree = 0;
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

void initialisation(void)
{
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontroleur n'est pas prêt...
    cli();
    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRA = 0xff;
    DDRD = 0x00;
    boutonPoussoir = 0;
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

int main()
{
    const uint8_t VERT = 0b01;
    const uint8_t ROUGE = 0b10;
    const uint8_t ETEINT = 0b00;
    initialisation();
    partirMinuterie(DUREE);
    do
    {
        PORTA = ROUGE;
        _delay_ms(100);
        PORTA = ETEINT;
        _delay_ms(100);
        // attendre qu'une des deux variables soit modifiée
        // par une ou l'autre des interruptions.
    }
    while (minuterieExpiree == 0);
    PORTA = ETEINT;
    partirMinuterie(SECONDE);
    do
    {
        continue;
        // attendre qu'une des deux variables soit modifiée
        // par une ou l'autre des interruptions.
    }
    while (minuterieExpiree == 0 && boutonPoussoir == 0);
    // Une interruption s'est produite. Arrêter toute
    // forme d'interruption. Une seule réponse suffit.
    cli();
    // Verifier la réponse
    if (boutonPoussoir == 1)
    {
        PORTA = VERT;
    }
    else PORTA = ROUGE;

    return 0;
}
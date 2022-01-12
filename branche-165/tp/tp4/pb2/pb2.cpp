/*Nom    : tp2, pb1
  équipe : 165
  Auteurs: Mymanat Mohammed - 2068301
           Safa Ikhlef      - 2058906

Tableau d'état pb1
État présent    D2    D3    État prochain    Sortie
    INIT        0     1         INIT         eteint  
    INIT        1     0         etat1        eteint
    etat1       0     1         etat3        rouge
    etat1       1     0         etat2        rouge
    etat2       0     1         INIT          vert
    etat2       1     0         INIT          vert
    etat3       0     1         etat2        eteint
    etat3       1     0         etat3        eteint

    */

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t BOUTOND2= 0x04;
const uint8_t BOUTOND3= 0x08;
const uint8_t VERT= 0x01;
const uint8_t ROUGE= 0x02;
const uint8_t ETEINT= 0x00;
volatile bool estAppuyeD2= false;
volatile bool estAppuyeD3= false;


volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir; 

ISR ( TIMER1_COMPA_vect) {

minuterieExpiree = 1;

}

ISR ( INT0_vect ) {

boutonPoussoir = 1;

// anti-rebond

_delay_ms ( 30 );

EIFR |= (1 << INTF0) ;

}

void partirMinuterie ( uint16_t duree ) {

minuterieExpiree = 0;

// mode CTC du timer 1 avec horloge divisée par 1024

// interruption après la durée spécifiée

TCNT1 = 0 ;

OCR1A = duree;

TCCR1A = (1 << COM1A1) |  (1 << COM1B1);

TCCR1B = (1 << ICES1) |  (1 << WGM12) | (1 << CS12) |  (1 << CS10);

TCCR1C = 0;

TIMSK1 =  (1 << ICIE1) |  (1 << OCIE1A);

}

void initialisation ( void ) 
{

    // cli est une routine qui bloque toutes les interruptions.

    // Il serait bien mauvais d'être interrompu alors que

    // le microcontroleur n'est pas prêt...

    cli ();

    // configurer et choisir les ports pour les entrées

    // et les sorties. DDRx... Initialisez bien vos variables

    DDRA=0xff;

    // cette procédure ajuste le registre EIMSK

    // de l’ATmega324PA pour permettre les interruptions externes

    EIMSK |= (1 << INT0);

    // il faut sensibiliser les interruptions externes aux

    // changements de niveau du bouton-poussoir

    // en ajustant le registre EICRA

    EICRA |= (1 << ISC00);

    // sei permet de recevoir à nouveau des interruptions.

    sei ();
}


int main()
{
    DDRD=0x00;
    initialisation();
    _delay_ms(10000);

    for(int i=0; i<10; i++)
    {
        PORTA= ROUGE;
        _delay_ms(10);
        PORTA= ETEINT;
    }

    do {

        PORTA= ETEINT;

        } while ( minuterieExpiree == 0 && boutonPoussoir == 0 );


    // Une interruption s'est produite. Arrêter toute

    // forme d'interruption. Une seule réponse suffit.

    cli ();

    // Verifier la réponse

    if (boutonPoussoir == 1)
    {
        while (boutonReset == 0){
        PORTA= VERT;
    else
        PORTA= ROUGE;
    }
    return 0;
}

/*

volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;
const uint16_t DUREE = 100000;
const uint16_t SECONDE = 1000;

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

int main()
{
    const uint8_t VERT = 0b01;
    const uint8_t ROUGE = 0b10;
    const uint8_t ETEINT = 0b00;
    initialisationMinuterie1();
    DDRA = 0xff;
    DDRD = 0x00;
    boutonPoussoir = 0;
    minuterieExpiree = 0;
    _delay_ms(DUREE);
    for (int i=0; i<50; i++)
    {
        PORTA = ROUGE;
        _delay_ms(100);
        PORTA = ETEINT;
        _delay_ms(100);
        // attendre qu'une des deux variables soit modifiée
        // par une ou l'autre des interruptions.
    } 
    PORTA = ETEINT;
    partirMinuterieTimer1ModeCTCPrescaler1024(SECONDE);
    minuterieExpiree == 0;
    do
    {
        // continue;
        PORTA = VERT;
        // attendre qu'une des deux variables soit modifiée
        // par une ou l'autre des interruptions.
    } while (minuterieExpiree == 0 && boutonPoussoir == 0);
    // Une interruption s'est produite. Arrêter toute
    // forme d'interruption. Une seule réponse suffit.
    cli();
    // Verifier la réponse
    if (boutonPoussoir == 1)
    {
        PORTA = VERT;
    }
    else
        PORTA = ROUGE;

    return 0;
}

*/
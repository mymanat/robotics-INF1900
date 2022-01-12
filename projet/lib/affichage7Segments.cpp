#define F_CPU 8000000
#include <avr/io.h>

#include "affichage7Segments.h"

#define moteurGauche 0
#define moteurDroite 1

void activer7Segments()
{
    DDRA |= 1 << PA7 | 1 << PA6 | 1 << PA5 | 1 << PA4;
    DDRB |= 1 << PB7 | 1 << PB6 | 1 << PB5;
    DDRC |= 1 << PC1 | 1 << PC0;
    DDRD |= 1 << PD7;
}

void desactiver7Segments()
{
    PORTC &= ~(1 << PC1) & ~(1 << PC0); // IE = 0
    PORTB |= 1 << PB7;
    PORTB &= ~(1 << PB6) & ~(1 << PB5); // IE = 0
    PORTD |= 1 << PD7;                  // OE = 1
}

void afficher7SegmentsDemarrage()
{
    //A gauche segment gauche
    uint8_t tampon = PORTA;
    PORTA = 1 << PA7 | 1 << PA5;
    PORTA |= tampon;

    PORTB |= 1 << PB5;
    PORTB &= ~(1 << PB6) & ~(1 << PB5);
    PORTC &= ~(1 << PC1) & ~(1 << PC0);
    PORTA &= ~(1 << PA7) & ~(1 << PA5);

    // B gauche segment droit
    tampon = PORTA;
    PORTA = 1 << PA7 | 1 << PA5 | 1 << PA4;
    PORTA |= tampon;

    PORTB |= 1 << PB6;
    PORTB &= ~(1 << PB6) & ~(1 << PB5);
    PORTC &= ~(1 << PC1) & ~(1 << PC0);
    PORTA &= ~(1 << PA7) & ~(1 << PA5) & ~(1 << PA4);

    //C droit segment gauche
    tampon = PORTA;
    PORTA = 1 << PA7 | 1 << PA6;
    PORTA |= tampon;

    PORTC |= 1 << PC0;
    PORTC &= ~(1 << PC1) & ~(1 << PC0);
    PORTB &= ~(1 << PB6) & ~(1 << PB5);
    PORTA &= ~(1 << PA7) & ~(1 << PA6);

    //D droit segment droit
    tampon = PORTA;
    PORTA = 1 << PA7 | 1 << PA6 | 1 << PA4;
    PORTA |= tampon;

    PORTC |= 1 << PC1;
    PORTC &= ~(1 << PC1) & ~(1 << PC0);
    PORTB &= ~(1 << PB6) & ~(1 << PB5);
    PORTA &= ~(1 << PA7) & ~(1 << PA6) & ~(1 << PA4);

    //Force portA A7-A4 a 0
    PORTA &= ~(1 << PA7) & ~(1 << PA6) & ~(1 << PA5) & ~(1 << PA4);
}

void afficherCaractere(uint8_t caractere)
{
    uint8_t tampon = PORTA;
    tampon &= 0b00001111;
    if (caractere == 0)
    {
        PORTA = 0 << PA7 | 0 << PA6 | 0 << PA5 | 0 << PA4;
        PORTA |= tampon;
    }
    else if (caractere == 1)
    {
        PORTA = 0 << PA7 | 0 << PA6 | 0 << PA5 | 1 << PA4;
        PORTA |= tampon;
    }
    else if (caractere == 2)
    {
        PORTA = 0 << PA7 | 0 << PA6 | 1 << PA5 | 0 << PA4;
        PORTA |= tampon;
    }
    else if (caractere == 3)
    {
        PORTA = 0 << PA7 | 0 << PA6 | 1 << PA5 | 1 << PA4;
        PORTA |= tampon;
    }
    else if (caractere == 4)
    {
        PORTA = 0 << PA7 | 1 << PA6 | 0 << PA5 | 0 << PA4;
        PORTA |= tampon;
    }
    else if (caractere == 5)
    {
        PORTA = 0 << PA7 | 1 << PA6 | 0 << PA5 | 1 << PA4;
        PORTA |= tampon;
    }
    else if (caractere == 6)
    {
        PORTA = 0 << PA7 | 1 << PA6 | 1 << PA5 | 0 << PA4;
        PORTA |= tampon;
    }
    else if (caractere == 7)
    {
        PORTA = 0 << PA7 | 1 << PA6 | 1 << PA5 | 1 << PA4;
        PORTA |= tampon;
    }
    else if (caractere == 8)
    {
        PORTA = 1 << PA7 | 0 << PA6 | 0 << PA5 | 0 << PA4;
        PORTA |= tampon;
    }
    else if (caractere == 9)
    {
        PORTA = 1 << PA7 | 0 << PA6 | 0 << PA5 | 1 << PA4;
        PORTA |= tampon;
    }
    else if (caractere == 10)
    {
        PORTA = 1 << PA7 | 0 << PA6 | 1 << PA5 | 0 << PA4;
        PORTA |= tampon;
    }
    else if (caractere == 11)
    {
        PORTA = 1 << PA7 | 0 << PA6 | 1 << PA5 | 1 << PA4;
        PORTA |= tampon;
    }
    else if (caractere == 12)
    {
        PORTA = 1 << PA7 | 1 << PA6 | 0 << PA5 | 0 << PA4;
        PORTA |= tampon;
    }
    else if (caractere == 13)
    {
        PORTA = 1 << PA7 | 1 << PA6 | 0 << PA5 | 1 << PA4;
        PORTA |= tampon;
    }
    else if (caractere == 14)
    {
        PORTA = 1 << PA7 | 1 << PA6 | 1 << PA5 | 0 << PA4;
        PORTA |= tampon;
    }
    else if (caractere == 15)
    {
        PORTA = 1 << PA7 | 1 << PA6 | 1 << PA5 | 1 << PA4;
        PORTA |= tampon;
    }
}

int puissanceSegmentDroit(uint8_t puissance, bool isDecimal)
{
    if (isDecimal)
    {
        return puissance % 10;
    }
    else
    {
        return puissance & 0b00001111;
    }
}

int puissanceSegmentGauche(uint8_t puissance, bool isDecimal)
{
    if (isDecimal)
    {
        return puissance / 10 % 10;
    }
    else
    {
        int tampon = 0;
        tampon = puissance & 0b11110000;
        tampon >>= 4;
        return tampon;
    }
}

void afficher7SegmentsChoix(uint8_t pourcentageMoteur, uint8_t moteur, bool isDecimal)
{
    uint8_t segmentGauche = puissanceSegmentGauche(pourcentageMoteur, isDecimal);
    uint8_t segmentDroit = puissanceSegmentDroit(pourcentageMoteur, isDecimal);
    if (moteur == moteurGauche)
    {
        PORTB &= ~(1 << PB7);
        PORTD &= ~(1 << PD7);

        if (segmentGauche != 0)
        {
            afficherCaractere(segmentGauche);
            PORTB |= 1 << PB5;
            PORTB &= ~(1 << PB5);
        }
        if (segmentGauche == 0)
        {
            afficherCaractere(0);
            PORTB |= 1 << PB5;
            PORTB &= ~(1 << PB5);
        }
        afficherCaractere(segmentDroit);
        PORTB |= 1 << PB6;
        PORTB &= ~(1 << PB6);
    }
    else if (moteur == moteurDroite)
    {
        PORTB &= ~(1 << PB7);
        PORTD &= ~(1 << PD7);

        if (segmentGauche != 0)
        {
            afficherCaractere(segmentGauche);
            PORTC |= 1 << PC0;
            PORTC &= ~(1 << PC0);
        }
        if (segmentGauche == 0)
        {
            afficherCaractere(0);
            PORTC |= 1 << PC0;
            PORTC &= ~(1 << PC0);
        }
        afficherCaractere(segmentDroit);
        PORTC |= 1 << PC1;
        PORTC &= ~(1 << PC1);
    }
}

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

enum Etat
{
    INIT,
    E1,
    E2,
    E3
};

// selon le nom de votre variable
// placer le bon type de signal d'interruption
// à prendre en charge en argument
volatile Etat etat = INIT;
volatile bool estAppuye = false;

ISR(INT0_vect)
{
    // laisser un delai avant de confirmer la réponse du
    // bouton-poussoir: environ 30 ms (anti-rebond)
    _delay_ms(30);
    // se souvenir ici si le bouton est pressé ou relâché
    estAppuye = !estAppuye;
    // changements d'états tels que ceux de la
    // semaine précédente
    if (etat == INIT)
    {
        etat = E1;
        estAppuye = !estAppuye;
    }

    else if (etat == E1)
    {
        etat = E2;
        estAppuye = !estAppuye;
    }
    else if (etat == E2)
    {
        etat = INIT;
        estAppuye = !estAppuye;
    }

    // Voir la note plus bas pour comprendre cette instruction et son rôle
    EIFR |= (1 << INTF0);
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
    initialisation();
    uint8_t vert = 0b01;
    uint8_t rouge = 0b10;
    uint8_t eteint = 0b00;

    for (;;)
    {
        switch (etat)
        {
        case INIT:
            PORTA = eteint;
            break;

        case E1:
            PORTA = rouge;
            break;

        case E2:
            PORTA = vert;
            break;

        default:
            PORTA = eteint;
            etat = INIT;
            break;
        }
    }
    return 0;
}
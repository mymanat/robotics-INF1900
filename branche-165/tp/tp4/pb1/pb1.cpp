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
const uint8_t VERT= 0x02;
const uint8_t ROUGE= 0x01;
const uint8_t ETEINT= 0x00;
enum Etat{INIT, etat1, etat2, etat3};
volatile Etat etatpresent= INIT;
volatile bool estAppuyeD2= false;
volatile bool estAppuyeD3= false;

ISR (INT0_vect) 
{

    // laisser un delai avant de confirmer la réponse du

    // bouton-poussoir: environ 30 ms (anti-rebond)

    _delay_ms ( 30 );

    // se souvenir ici si le bouton est pressé ou relâché

    estAppuyeD2 = !estAppuyeD2;

    // changements d'états tels que ceux de la

    // semaine précédente

    if (etatpresent == INIT)
        etatpresent= etat1;

    else if (etatpresent == etat1)
        etatpresent= etat2;

    else if (etatpresent == etat2)
        etatpresent= INIT;
    // Voir la note plus bas pour comprendre cette instruction et son rôle

    EIFR |= (1 << INTF0) ;

}

ISR (INT1_vect) 
{

    // laisser un delai avant de confirmer la réponse du

    // bouton-poussoir: environ 30 ms (anti-rebond)

    _delay_ms ( 30 );

    // se souvenir ici si le bouton est pressé ou relâché

    estAppuyeD3 = !estAppuyeD3;

    // changements d'états tels que ceux de la

    // semaine précédente

     if (etatpresent == etat1)
        etatpresent= etat3;

     else if (etatpresent == etat2)
        etatpresent= INIT;

     else if (etatpresent == etat3)
        etatpresent= etat2;
    // Voir la note plus bas pour comprendre cette instruction et son rôle

    EIFR |= (1 << INTF0) ;
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

    EIMSK |= (1 << INT0)| (1 << INT1);

    // il faut sensibiliser les interruptions externes aux

    // changements de niveau du bouton-poussoir

    // en ajustant le registre EICRA

    EICRA |= (1 << ISC00)| (1 << ISC01);

    // sei permet de recevoir à nouveau des interruptions.

    sei ();
}


int main()
{
    DDRD=0x00;
    initialisation();

    for (;;)
    {
        switch (etatpresent)
        {
            case INIT:
                if (estAppuyeD2 == true)
                {
                    PORTA = ROUGE;
                }
                break;

            case etat1:
                if (estAppuyeD2 == true)
                {
                    PORTA = VERT;
                }

                else if (estAppuyeD3 == true)
                {
                    PORTA =ETEINT;
                }
                break;

            case etat2:
                if ((estAppuyeD2 == true) | (estAppuyeD3 == true))
                {
                    PORTA = ETEINT;
                };
                break;
            
            case etat3:
                if (estAppuyeD3 == true)
                {
                    PORTA = VERT;
                }
                break;
        }   
    }
    return 0;
}
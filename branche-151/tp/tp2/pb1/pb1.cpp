///////////////////////////////////////////////////////////////
//Machine à états de Moore contrôlant l'allumage d'une LED
//Date : 29/01/2021
//Auteur : Ivan Ivanov et Eliott Schuhmacher-Wantz
//Matricules : 2087256 et 2081542
//Groupe 151
///////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//État présent   Entrée D2    D3    État suivant     Sortie D
//INIT                  0     X           INIT         ETEINT
//INIT                  1     X           E1           VERT
//E1                    X     0           E1           VERT
//E1                    X     1           E2           VERT
//E2                    X     0           E2           VERT
//E2                    X     1           E3           VERT
//E3                    X     0           E3           VERT
//E3                    X     1           E4           VERT
//E4                    X     X           INIT         ROUGE
///////////////////////////////////////////////////////////////

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

int main()
{
    DDRA = 0xff;
    DDRD = 0x00;
    unsigned short vert = 0b01;
    unsigned short rouge = 0b10;
    unsigned short eteint = 0b00;
    int delaiAntirebond = 10;
    int seconde = 1000;
    enum etat
    {
        INIT,
        E1,
        E2,
        E3,
        E4
    };
    etat etatSuivant = INIT;

    for (;;)
    {
        switch (etatSuivant)
        {
        case INIT:
            PORTA = eteint;
            if (PIND & 0x04)
            {
                _delay_ms(delaiAntirebond);
                if (PIND & 0x04)
                {
                    while (PIND & 0x04)
                    {
                        continue;
                    }
                    etatSuivant = E1;
                    break;
                }
            }
            else
            {
                etatSuivant = INIT;
            }
            break;

        case E1:
            PORTA = vert;
            if (PIND & 0x08)
            {
                _delay_ms(delaiAntirebond);
                if (PIND & 0x08)
                {
                    while (PIND & 0x08)
                    {
                        continue;
                    }
                    etatSuivant = E2;
                    break;
                }
            }
            else
            {
                etatSuivant = E1;
            }
            break;

        case E2:
            PORTA = vert;
            if (PIND & 0x08)
            {
                _delay_ms(delaiAntirebond);
                if (PIND & 0x08)
                {
                    while (PIND & 0x08)
                    {
                        continue;
                    }
                    etatSuivant = E3;
                    break;
                }
            }
            else
            {
                etatSuivant = E2;
            }
            break;

        case E3:
            PORTA = vert;
            if (PIND & 0x08)
            {
                _delay_ms(delaiAntirebond);
                if (PIND & 0x08)
                {
                    while (PIND & 0x08)
                    {
                        continue;
                    }
                    etatSuivant = E4;
                    break;
                }
            }
            else
            {
                etatSuivant = E3;
            }
            break;

        case E4:
            PORTA = rouge;
            _delay_ms(seconde);
            etatSuivant = INIT;
            break;

        default:
            PORTA = eteint;
            break;
        }
    }
    return 0;
}

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

int main()
{
    DDRA = 0xff;
    DDRD = 0x00;
    unsigned short vert = 0b01;
    unsigned short rouge = 0b10;
    unsigned short eteint = 0b00;
    int delaiAntirebond = 10;

    enum etat
    {
        INIT,
        E1,
        E2,
        E3
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
            PORTA = rouge;
            if (PIND & 0x04)
            {
                _delay_ms(delaiAntirebond);
                if (PIND & 0x04)
                {
                    while (PIND & 0x04)
                    {
                        continue;
                    }
                    etatSuivant = E2;
                    break;
                }
            }
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
                etatSuivant = E1;
            }
            break;

        case E2:
            PORTA = vert;
            if ((PIND & 0x04) || (PIND & 0x08))
            {
                _delay_ms(delaiAntirebond);
                if ((PIND & 0x04) || (PIND & 0x08))
                {
                    while ((PIND & 0x04) || (PIND & 0x08))
                    {
                        continue;
                    }
                    etatSuivant = INIT;
                    break;
                }
            }
            else
            {
                etatSuivant = E2;
            }
            break;

        case E3:
            PORTA = eteint;
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
                etatSuivant = E3;
            }
            break;

        default:
            PORTA = eteint;
            etatSuivant = INIT;
            break;
        }
    }
    return 0;
}
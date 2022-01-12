/*
  Nom    : tp8, exec
  Description : programme qui teste que la librairie créée
                fonctionne correctement en incluant les .h de la librairie
                et en appelant des fonctions de la librairie (main bidon)
  équipe : 115165
  Auteurs: Mymanat Mohammed - 2068301
           Safa Ikhlef      - 2058906
           Ivan Ivanov      - 2087256
           Eliott Schuhmacher-Wantz - 2081542
 */

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "debug.h"
#include "memoire.h"

char tableau[] = {"*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*\n\n"};

int main()
{
    DEBUG_PRINT(tableau);
    DDRA = 0xff;
    DDRD = 0x00;
    uint8_t vert = 0b01;
    uint8_t rouge = 0b10;
    uint8_t eteint = 0b00;
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
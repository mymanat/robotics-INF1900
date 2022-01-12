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

bool debounce(int bouton)
{
   if (PIND & bouton)
    {
        _delay_ms(10);
        if (PIND & bouton)
        {
            return true;
        }
    }
    return false;
}


int main()
{
    DDRA= 0xff;
    DDRD=0x00;
    const int boutonD2= 0x04;
    const int boutonD3= 0x08;
    const int vert= 0x01;
    const int rouge= 0x02;
    const int eteint= 0x00;
    enum Etat{INIT, etat1, etat2, etat3};
    Etat etatpresent= INIT;

    for (;;)
    {
        switch (etatpresent)
        {
            case INIT:
                if (debounce(boutonD2))
                {
                    PORTA = rouge;
                    etatpresent = etat1;
                    _delay_ms(100);
                }
                break;

            case etat1:
                if (debounce(boutonD2))
                {
                    PORTA = vert;
                    etatpresent = etat2;
                    _delay_ms(100);
                }
                else
                {
                    if (debounce(boutonD3))
                    {
                        PORTA = eteint;
                        etatpresent = etat3;
                        _delay_ms(100);
                    }
                }
                break;

            case etat2:
                if (debounce(boutonD2) | debounce(boutonD3))
                {
                    PORTA = eteint;
                    etatpresent = INIT;
                    _delay_ms(100);
                }
                break;
            
            case etat3:
                if (debounce(boutonD3))
                {
                    PORTA = vert;
                    etatpresent = etat2;
                    _delay_ms(100);
                }
                break;
        }   
       
    }
    return 0;
}
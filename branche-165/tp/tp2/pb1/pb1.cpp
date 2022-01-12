/*Nom    : tp2, pb1
  équipe : 165
  Auteurs: Mymanat Mohammed - 2068301
           Safa Ikhlef      - 2058906

Tableau d'état pb1
État présent    D2    D3    État prochain    Sortie
    INIT        0     1         INIT         eteint  
    INIT        1     0         etat1        eteint
    etat1       1     0         etat1         vert
    etat1       0     1         etat2         vert
    etat2       1     0         etat2         vert
    etat2       0     1         etat3         vert
    etat3       1     0         etat3         vert
    etat3       0     1         etat4         vert
    etat4       x     x         INIT         rouge  **conserve la lumiere rouge pendant 1 seconde par l'ajout d'un delais dans le code**
    **pour le diagramme d'etat, on a 5 etats. Cependant, les etats 3 et 4 sont remplacés par un compteur incrémenté a chaque fois que le bouton D3 est pesee dans notre code**
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
    const double delais=1000;
    int compteur_bouton=0;
    enum Etat{INIT, etat1, etat2};
    Etat etatpresent= INIT;

    for (;;)
    {
    
        switch (etatpresent)
        {
            case INIT:
                if (debounce(boutonD2))
                {
                    PORTA = vert;
                    etatpresent = etat1;
                    _delay_ms(100);
                }
                break;

            case etat1:
                if (debounce(boutonD3))
                {
                    PORTA = vert;
                    compteur_bouton++;
                    _delay_ms(100);
                }

                if (compteur_bouton == 3)
                {
                    PORTA = vert;
                    compteur_bouton = 0;
                    etatpresent = etat2;
                }
                break;

            case etat2:
                PORTA=rouge;
                _delay_ms(delais);
                PORTA= eteint;
                etatpresent= INIT;
                _delay_ms(100);
                break;

        }   
       
    }
    return 0;
}















/*
  Nom    : tp7, lib
  Description : programme qui regroupe plusieurs fonctions
                utiles en lien les del comme les allumer ou
                changer leur couleur
  équipe : 115165
  Auteurs: Mymanat Mohammed - 2068301
           Safa Ikhlef      - 2058906
           Ivan Ivanov 
           Eliott Schuhmacher-Wantz 
 */

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000
#define SORTIE 0xff
#define ENTREE 0x00
#define VERT 0x01
#define ROUGE 0x02
#define DELAIS 10

void allumerDel(const uint8_t couleur, volatile uint8_t &port)
{
    port = couleur;
}

void allumerDelAmbre(volatile uint8_t &port)
{
    port = VERT;
    _delay_ms(DELAIS);
    port = ROUGE;
    _delay_ms(DELAIS);
}

bool antiRebond(const uint8_t bouton)
{
    DDRD = ENTREE;
    if (PIND & bouton)
    {
        _delay_ms(DELAIS);
        if (PIND & bouton)
        {
            return true;
        }
    }
    return false;
}

void allumerDelBouton(const uint8_t couleur, const uint8_t bouton, volatile uint8_t &port)
{
    DDRD = ENTREE;
    if (antiRebond(bouton))
    {
        allumerDel(couleur, port);
    }
}
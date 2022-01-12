/*
  Nom    : tp6, pb1
  Description : programme qui fait varier la couleur d'une DEL
                en fonction de l'intensité lumineuse 
  équipe : 165
  Auteurs: Mymanat Mohammed - 2068301
           Safa Ikhlef      - 2058906
 */

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include "can.h"

int main()
{
  const int SORTIE = 0xff;
  const int ENTREE = 0x00;
  DDRB = SORTIE; // PORT B est en mode sortie
  DDRA = ENTREE; // PORT A est en mode entrée
  const int VERT = 0x01;
  const int ROUGE = 0x02;
  const int DELAIS = 10;
  uint16_t lumBasse = 2.4/4*255; //seuil où la lumière est très basse
  uint16_t lumAmbiante = 3.0/4*255; //seuil maximal où la lumière est considérée ambiante, 
                                  //si ce seuil est dépassé, la lumière est considérée forte
 

  uint16_t lecture; // --> 0 à 255
  can convertir = can();

  for (;;) // boucle sans fin
  {
    lecture = convertir.lecture(0) >> 2; // lecture --> entre 0 et 255

    // L'intensité lumineuse est basse, la lumière est donc verte
    if (lecture < lumBasse) 
      PORTB = VERT;

    // L'intensité lumineuse est moyenne(lumière ambiante) (plus grande que la lumière basse, mais plus petite 
    //que le seuil maximal pour être considéré ambiant),la lumière est donc ambré
    if ((lecture >= lumBasse) && (lecture < lumAmbiante))
    {
      PORTB = VERT;
      _delay_ms(DELAIS);
      PORTB = ROUGE;
      _delay_ms(DELAIS);
    }

    // L'intensité lumineuse est forte, la lumière est donc rouge
    if (lecture >= lumAmbiante)
      PORTB = ROUGE;    
  }
  return 0;
}

#include <avr/io.h>
#include <util/delay.h>
#include "can.h"
#define F_CPU 8000000
#define SORTIE 0xff
#define VERT 0x01
#define ROUGE 0x02
#define DELAIS 10
#define D4 0x10
#define D5 0x20

void ajusterDelCan(const uint8_t palier1, const uint8_t palier2, const uint8_t palier3)
{
  can objet = can();
  while (true)
  {
    uint16_t adcVal = objet.lecture(0);
    if (adcVal >= palier1 && adcVal < palier2)
    {
      PORTB = VERT;
    }
    else if (adcVal >= palier2 && adcVal < palier3)
    {
      while (adcVal >= palier2 && adcVal < palier3)
      {
        PORTB = ROUGE;
        _delay_ms(DELAIS);
        PORTB = VERT;
        _delay_ms(DELAIS);
        uint16_t adcVal = objet.lecture(0);
        if (adcVal < palier2 || adcVal >= palier3)
        {
          break;
        }
      }
    }
    else if (adcVal >= palier3)
    {
      PORTB = ROUGE;
    }
  }
}

void ajusterDelPWM(uint16_t pourcentage, uint16_t signal)
{
  DDRD = SORTIE;
    
    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5
    // page 130 de la description technique du ATmega324PA)

    if (signal == D4)
    {
      OCR1B = pourcentage;  //D4
    }
    if (signal == D5)
    {
      OCR1A = pourcentage;  //D5
    }
        
    // division d'horloge par 8 - implique une frequence de PWM fixe

    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B = (1 << ICES1) | (1 << CS11);
    TCCR1C = 0;
}

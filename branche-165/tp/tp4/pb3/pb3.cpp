
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h> 


void ajustementPWM(uint16_t pourcentage1, uint16_t pourcentage2)
{
    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5
    // page 130 de la description technique du ATmega324PA)
    
    OCR1A = pourcentage1;
    OCR1B = pourcentage2;
    // division d'horloge par 8 - implique une frequence de PWM fixe

    TCCR1A = (1 << COM1A1)  | (1 << COM1B1)  | (1 << WGM10);
    TCCR1B = (1 << ICES1) |(1 << CS11);
    TCCR1C = 0;

}

int main()
{
  DDRD = 0xff;
  PORTD = 0x40;
  PORTD = 0x01;

  for(;;)
  {
    ajustementPWM(0, 0);     //0 = 0%
    _delay_ms(2000);
    ajustementPWM(64, 64);   //64 = 25%
    _delay_ms(2000);
    ajustementPWM(128, 128); //128 = 50%
    _delay_ms(2000);
    ajustementPWM(191, 191); //191 = 75%
    _delay_ms(2000);
    ajustementPWM(254, 254); //254 = 100%
    _delay_ms(2000);
  
  }

  return 0; 
}




